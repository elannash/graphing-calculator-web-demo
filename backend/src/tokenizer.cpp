#include "../include/tokenizer.h"
#include <iostream>
#include <cctype>
#include <set>
#include <algorithm>
#include <cstring>

bool is_math_function(const std::string &str)
{
    static const std::set<std::string> functions = {
        "ABS", "NEG", "COS", "SIN", "TAN", "SEC", "CSC", "COT",
        "ARCCOS", "ARCSIN", "ARCTAN", "ARCSEC", "ARCCSC", "ARCCOT",
        "SINH", "COSH", "TANH", "SECH", "CSCH", "COTH",
        "ARCSINH", "ARCCOSH", "ARCTANH", "ARCSECH", "ARCCSCH", "ARCCOTH",
        "LOG", "LN", "SQRT", "EXP", "LOG2", "EXP10", "EXP2", "CBRT",
        "GAMMA", "ERF", "ERFC", "CEIL"};
    return (functions.find(str) != functions.end());
}

bool is_special_function(const std::string &str)
{
    static const std::set<std::string> special_functions = {"MAX", "MIN", "POW"};
    return (special_functions.find(str) != special_functions.end());
}

bool is_variable(const std::string &str)
{
    return (str == "X");
}

bool is_number(const std::string &str)
{
    if (str.empty())
        return false;
    bool seenDecimal = false;
    for (char c : str)
    {
        if (std::isdigit(static_cast<unsigned char>(c)))
            continue;
        if (c == '.' && !seenDecimal)
        {
            seenDecimal = true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool last_token_is_value_like(Queue<Token *> &q)
{
    if (q.empty())
        return false;
    Token *back = q.back();
    int t = back->type_of();
    return (t == NUMBER || t == VARIABLE || t == RIGHTPAREN);
}

void Tokenizer::finalize_token(const std::string &token_str, Queue<Token *> &q)
{
    if (token_str.empty())
        return;

    if (is_number(token_str))
    {
        q.push(new Number(std::stof(token_str)));
    }
    else if (is_variable(token_str))
    {
        q.push(new Variable(token_str));
    }
    else if (is_math_function(token_str))
    {
        q.push(new Function(token_str));
    }
    else if (is_special_function(token_str))
    {
        q.push(new SpecialFunction(token_str));
    }
    else if (token_str == "+" || token_str == "-" || token_str == "*" ||
             token_str == "/" || token_str == "^")
    {
        q.push(new Operator(token_str));
    }
    else if (token_str == "(")
    {
        q.push(new LeftParen());
    }
    else if (token_str == ")")
    {
        q.push(new RightParen());
    }
    else if (token_str == ",")
    {
        q.push(new ArgumentSeparator());
    }
    else
    {
        q.push(new ErrorToken("Unknown token: " + token_str));
    }
}

void Tokenizer::parse_letter_buffer(const std::string &letters, Queue<Token *> &q, bool &justSkippedComma)
{
    std::size_t i = 0;
    while (i < letters.size())
    {
        if (letters[i] == 'X')
        {
            if (last_token_is_value_like(q) && !justSkippedComma)
            {
                finalize_token("*", q);
            }
            finalize_token("X", q);
            justSkippedComma = false; // reset after finalizing this piece
            i++;
            continue;
        }

        bool foundFunc = false;
        for (std::size_t len = letters.size() - i; len > 0; len--)
        {
            std::string candidate = letters.substr(i, len);
            if (is_math_function(candidate) || is_special_function(candidate))
            {
                if (last_token_is_value_like(q) && !justSkippedComma)
                {
                    finalize_token("*", q);
                }
                finalize_token(candidate, q);
                justSkippedComma = false; // reset after finalizing function
                i += len;
                foundFunc = true;
                break;
            }
        }
        if (!foundFunc)
        {
            q.push(new ErrorToken("Unknown letter token: " + letters.substr(i, 1)));
            i++;
        }
    }
}

Tokenizer::Tokenizer(std::string pre_tokenized_str)
    : _pre_tokenized_str(pre_tokenized_str)
{
}

Queue<Token *> Tokenizer::get_tokenized_q()
{
    Queue<Token *> post_tokenized_q;
    std::string input = _pre_tokenized_str;

    for (char &c : input)
    {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    std::string letterBuf;
    std::string numberBuf;
    bool justSkippedComma = false;

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        char c = input[i];
        if (std::isspace((unsigned char)c))
        {
            continue;
        }

        if (std::isalpha((unsigned char)c))
        {
            if (!numberBuf.empty())
            {
                finalize_token(numberBuf, post_tokenized_q);
                numberBuf.clear();
                if (last_token_is_value_like(post_tokenized_q) && !justSkippedComma)
                {
                    finalize_token("*", post_tokenized_q);
                }
            }
            letterBuf.push_back(c);

            if ((i + 1 == input.size()) || !std::isalpha((unsigned char)input[i + 1]))
            {
                parse_letter_buffer(letterBuf, post_tokenized_q, justSkippedComma);
                letterBuf.clear();
            }
        }
        else if (std::isdigit((unsigned char)c) || c == '.')
        {
            if (!letterBuf.empty())
            {
                parse_letter_buffer(letterBuf, post_tokenized_q, justSkippedComma);
                letterBuf.clear();
                if (last_token_is_value_like(post_tokenized_q) && !justSkippedComma)
                {
                    finalize_token("*", post_tokenized_q);
                }
            }
            if (last_token_is_value_like(post_tokenized_q) && numberBuf.empty() && !justSkippedComma)
            {
                finalize_token("*", post_tokenized_q);
            }
            numberBuf.push_back(c);

            if ((i + 1 == input.size()) ||
                !(std::isdigit((unsigned char)input[i + 1]) || input[i + 1] == '.'))
            {
                finalize_token(numberBuf, post_tokenized_q);
                numberBuf.clear();
                justSkippedComma = false;
            }
        }
        else if (std::strchr("+-*/^()", c))
        {
            if (!letterBuf.empty())
            {
                parse_letter_buffer(letterBuf, post_tokenized_q, justSkippedComma);
                letterBuf.clear();
            }
            if (!numberBuf.empty())
            {
                finalize_token(numberBuf, post_tokenized_q);
                numberBuf.clear();
            }

            if (c == '(')
            {
                bool lastWasFunc = false;
                if (!post_tokenized_q.empty())
                {
                    int t = post_tokenized_q.back()->type_of();
                    if (t == FUNCTION || t == SPECIAL_FUNCTION)
                    {
                        lastWasFunc = true;
                    }
                }
                if (!lastWasFunc && last_token_is_value_like(post_tokenized_q) && !justSkippedComma)
                {
                    finalize_token("*", post_tokenized_q);
                }
            }
            finalize_token(std::string(1, c), post_tokenized_q);
            justSkippedComma = false;
        }
        else if (c == ',')
        {
            if (!letterBuf.empty())
            {
                parse_letter_buffer(letterBuf, post_tokenized_q, justSkippedComma);
                letterBuf.clear();
            }
            if (!numberBuf.empty())
            {
                finalize_token(numberBuf, post_tokenized_q);
                numberBuf.clear();
            }

            finalize_token(",", post_tokenized_q);
            justSkippedComma = true;
        }
        else
        {
            std::cerr << "Unknown character: " << c << std::endl;
            justSkippedComma = false;
        }
    }

    if (!letterBuf.empty())
    {
        parse_letter_buffer(letterBuf, post_tokenized_q, justSkippedComma);
        letterBuf.clear();
    }
    if (!numberBuf.empty())
    {
        finalize_token(numberBuf, post_tokenized_q);
        numberBuf.clear();
    }

    return post_tokenized_q;
}

Queue<Token *> Tokenizer::operator()()
{
    return get_tokenized_q();
}

void Tokenizer::set_pre_tokenized_str(std::string str)
{
    _pre_tokenized_str = str;
}

std::string Tokenizer::get_pre_tokenized_str()
{
    return _pre_tokenized_str;
}
