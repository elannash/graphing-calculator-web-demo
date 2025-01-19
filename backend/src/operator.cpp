#include "../include/operator.h"

Operator::Operator(string Token_str)
    : Token(Token_str, OPERATOR), _op(Token_str), _isUnary(false)
{
    // set precedence based on operator type
    if (Token_str == "+" || Token_str == "-")
    {
        _precedence = 1; // default precedence for addition and subtraction
    }
    else if (Token_str == "*" || Token_str == "/")
    {
        _precedence = 2; // multiplication and division
    }
    else if (Token_str == "^")
    {
        _precedence = 3; // exponentiation
    }
    else
    {
        _precedence = 0; // default for unknown operators (shouldn't happen)
    }
}

double Operator::evaluate(double lhs, double rhs) const
{
    // Evaluate binary operators
    if (_op == "+")
    {
        return lhs + rhs;
    }
    if (_op == "-")
    {
        return lhs - rhs;
    }
    if (_op == "*")
    {
        return lhs * rhs;
    }
    if (_op == "/")
    {
        if (rhs == 0)
        {
            throw std::runtime_error("Division by zero.");
        }
        return lhs / rhs;
    }
    if (_op == "^")
    {
        return pow(lhs, rhs);
    }

    assert(false && "_op is not a valid binary operator");
    return 0;
}

double Operator::evaluate(double unary) const
{
    if (_op == "+")
    {
        return unary;
    }
    if (_op == "-")
    {
        return -unary;
    }

    assert(false && "_op is not a valid unary operator");
    return 0;
}

int Operator::get_prec() const
{
    return _precedence;
}

void Operator::set_prec(int precedence)
{
    _precedence = precedence;
}

void Operator::set_as_unary()
{
    _isUnary = true;
    _precedence = 4; // higher precedence for unary +/-
}

bool Operator::is_unary() const
{
    return _isUnary;
}

string Operator::get_op() const
{
    return _op;
}

TOKEN_TYPES Operator::type_of() const
{
    return OPERATOR;
}

ostream &Operator::print(ostream &outs) const
{
    outs << _op;
    return outs;
}

void Operator::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of() << endl
         << "OPERATOR: " << _op << endl
         << "PRECEDENCE: " << _precedence << endl
         << "IS_UNARY: " << (_isUnary ? "true" : "false") << endl;
}
