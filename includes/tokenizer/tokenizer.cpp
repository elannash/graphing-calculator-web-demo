#include "tokenizer.h"

bool is_number(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
        return true;
    }
}

Tokenizer::Tokenizer(string pre_tokenized_str) : _pre_tokenized_str(pre_tokenized_str) {}

Queue<Token *> Tokenizer::get_tokenized_q()
{
    Queue<Token *> post_tokenized_q; //make a copy so that private member variable doesn't need to be reset when changing string
                                     //not that important for this project, but useful for debugging

    char *cstr = new char[_pre_tokenized_str.size() + 1]; //need to declare a cstring to use strtok

    strcpy(cstr, _pre_tokenized_str.c_str()); //copying pre tokenized string into a cstring

    string str = "";

    //each loop, str gets appended with a character from the cstring
    //if statements are used to check if the string matches a token,
    //if it does, then a token is pushed into the post_tokenized_q and the str string is reset

    //there are some special checks for functions that contain the names of other functions, such as: sinh, cosh, tanh, which each contain the name of their respective trig functions
    //in this case, the token will not be pushed into the queue, and the loop will continue

    //a similar check is done for numbers
    //while the next char in the cstring is a number, it will keep getting appended to str

    //this is not at all an elegant solution
    for (int i = 0; i < strlen(cstr); i++)
    {
        str += toupper(cstr[i]);

        //delimiters
        if (str == "Y")
        {
            str = "";
        }
        else if (str == "=")
        {
            str = "";
        }
        else if (str == ",")
        {
            str = "";
        }
        else if (str == " ")
        {
            str = "";
        }

        //numbers
        else if (is_number(str))
        {
            //check if next char is number before pushing
            //using this while loop to check if next char is also number
            while (isdigit(cstr[i + 1]) || cstr[i + 1] == '.')
            {
                i++;
                str += cstr[i];
            }
            post_tokenized_q.push(new Number(stof(str)));
            str = "";
        }

        //variables
        else if (str == "X")
        {
            post_tokenized_q.push(new Variable("X"));
            str = "";
        }

        //operators
        else if (str == "+")
        {
            post_tokenized_q.push(new Operator("+"));
            str = "";
        }
        else if (str == "-")
        {
            post_tokenized_q.push(new Operator("-"));
            str = "";
        }
        else if (str == "*")
        {
            post_tokenized_q.push(new Operator("*"));
            str = "";
        }
        else if (str == "/")
        {
            post_tokenized_q.push(new Operator("/"));
            str = "";
        }
        else if (str == "^")
        {
            post_tokenized_q.push(new Operator("^"));
            str = "";
        }

        //functions
        else if (str == "ABS")
        {
            post_tokenized_q.push(new Function("ABS"));
            str = "";
        }
        else if (str == "NEG")
        {
            post_tokenized_q.push(new Function("NEG"));
            str = "";
        }
        else if (str == "COS")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("COS"));
                str = "";
            }
        }
        else if (str == "SIN")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("SIN"));
                str = "";
            }
        }
        else if (str == "TAN")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("TAN"));
                str = "";
            }
        }
        else if (str == "SEC")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("SEC"));
                str = "";
            }
        }
        else if (str == "CSC")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("CSC"));
                str = "";
            }
        }
        else if (str == "COT")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("COT"));
                str = "";
            }
        }
        else if (str == "ARCCOS")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("ARCCOS"));
                str = "";
            }
        }
        else if (str == "ARCSIN")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("ARCSIN"));
                str = "";
            }
        }
        else if (str == "ARCTAN")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("ARCTAN"));
                str = "";
            }
        }
        else if (str == "ARCSEC")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("ARCSEC"));
                str = "";
            }
        }
        else if (str == "ARCCSC")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("ARCCSC"));
                str = "";
            }
        }
        else if (str == "ARCCOT")
        {
            if (!(toupper(cstr[i + 1]) == 'H'))
            {
                post_tokenized_q.push(new Function("ARCCOT"));
                str = "";
            }
        }
        else if (str == "COSH")
        {
            post_tokenized_q.push(new Function("COSH"));
            str = "";
        }
        else if (str == "SINH")
        {
            post_tokenized_q.push(new Function("SINH"));
            str = "";
        }
        else if (str == "TANH")
        {
            post_tokenized_q.push(new Function("TANH"));
            str = "";
        }
        else if (str == "SECH")
        {
            post_tokenized_q.push(new Function("SECH"));
            str = "";
        }
        else if (str == "CSCH")
        {
            post_tokenized_q.push(new Function("CSCH"));
            str = "";
        }
        else if (str == "COTH")
        {
            post_tokenized_q.push(new Function("COTH"));
            str = "";
        }
        else if (str == "ARCCOSH")
        {
            post_tokenized_q.push(new Function("ARCCOSH"));
            str = "";
        }
        else if (str == "ARCSINH")
        {
            post_tokenized_q.push(new Function("ARCSINH"));
            str = "";
        }
        else if (str == "ARCTANH")
        {
            post_tokenized_q.push(new Function("ARCTANH"));
            str = "";
        }
        else if (str == "ARCSECH")
        {
            post_tokenized_q.push(new Function("ARCSECH"));
            str = "";
        }
        else if (str == "ARCCSCH")
        {
            post_tokenized_q.push(new Function("ARCCSCH"));
            str = "";
        }
        else if (str == "ARCCOTH")
        {
            post_tokenized_q.push(new Function("ARCCOTH"));
            str = "";
        }
        else if (str == "LOG")
        {
            post_tokenized_q.push(new Function("LOG"));
            str = "";
        }
        else if (str == "LN")
        {
            post_tokenized_q.push(new Function("LN"));
            str = "";
        }
        else if (str == "SQRT")
        {
            post_tokenized_q.push(new Function("SQRT"));
            str = "";
        }

        //special functions
        else if (str == "MAX")
        {
            post_tokenized_q.push(new SpecialFunction("MAX"));
            str = "";
        }
        else if (str == "MIN")
        {
            post_tokenized_q.push(new SpecialFunction("MIN"));
            str = "";
        }
        else if (str == "POW")
        {
            post_tokenized_q.push(new SpecialFunction("POW"));
            str = "";
        }

        //parentheses
        else if (str == "(")
        {
            post_tokenized_q.push(new LeftParen);
            str = "";
        }
        else if (str == ")")
        {
            post_tokenized_q.push(new RightParen);
            str = "";
        }
    }

    delete[] cstr;

    //prevents invalid queue from being sent into shunting yard & rpn
    //checks if the queue is not empty
    //if the queue is not empty, it checks if the token at the back is a function or operator or left parantheses (which require another value after them)
    //this clears the queue before sending to sy/rpn

    //otherwise the normal infix queue is sent to shunting yard & rpn

    //this is a bad way to handle errors
    if (!post_tokenized_q.empty())
    {
        if (post_tokenized_q.back()->type_of() == FUNCTION || post_tokenized_q.back()->type_of() == SPECIAL_FUNCTION || post_tokenized_q.back()->type_of() == OPERATOR || post_tokenized_q.back()->type_of() == LEFTPAREN)
        {
            post_tokenized_q.clear();
        }
    }

    _post_tokenized_q = post_tokenized_q;
    return _post_tokenized_q;
}

Queue<Token *> Tokenizer::operator()()
{
    return get_tokenized_q();
}

void Tokenizer::set_pre_tokenized_str(string str)
{
    _pre_tokenized_str = str;
}

string Tokenizer::get_pre_tokenized_str()
{
    return _pre_tokenized_str;
}