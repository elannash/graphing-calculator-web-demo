#include "operator.h"

Operator::Operator(string Token_str) : Token(Token_str, OPERATOR), _op(Token_str)
{
    if (Token_str == "+" || Token_str == "-")
    {
        _precedence = 0;
    }
    else if (Token_str == "*" || Token_str == "/")
    {
        _precedence = 1;
    }
    else
    {
        _precedence = 2;
    }
}

double Operator::evaluate(double lhs, double rhs) const
{
    //need to deal with unary operators,
    //probably overload this

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
        return lhs / rhs;
    }
    if (_op == "^")
    {
        return pow(lhs, rhs);
    }

    assert(false && "_op is not of a valid type");

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
}

int Operator::get_prec() const
{
    return _precedence;
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
         << "OPERATOR: " << _op;
}