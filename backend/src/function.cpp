#include "../include/function.h"

Function::Function(string Token_str) : Operator(Token_str) {}

double Function::evaluate(double number) const
{
    if (get_op() == "ABS")
    {
        return abs(number);
    }
    if (get_op() == "NEG")
    {
        return -number;
    }
    if (get_op() == "COS")
    {
        return cos(number);
    }
    if (get_op() == "SIN")
    {
        return sin(number);
    }
    if (get_op() == "TAN")
    {
        return tan(number);
    }
    if (get_op() == "SEC")
    {
        return 1 / cos(number);
    }
    if (get_op() == "CSC")
    {
        return 1 / sin(number);
    }
    if (get_op() == "COT")
    {
        return 1 / tan(number);
    }
    if (get_op() == "ARCCOS")
    {
        return acos(number);
    }
    if (get_op() == "ARCSIN")
    {
        return asin(number);
    }
    if (get_op() == "ARCTAN")
    {
        return atan(number);
    }
    if (get_op() == "ARCSEC")
    {
        return 1 / acos(number);
    }
    if (get_op() == "ARCCSC")
    {
        return 1 / asin(number);
    }
    if (get_op() == "ARCCOT")
    {
        return 1 / atan(number);
    }
    if (get_op() == "COSH")
    {
        return cosh(number);
    }
    if (get_op() == "SINH")
    {
        return sinh(number);
    }
    if (get_op() == "TANH")
    {
        return tanh(number);
    }
    if (get_op() == "SECH")
    {
        return 1 / cosh(number);
    }
    if (get_op() == "CSCH")
    {
        return 1 / sinh(number);
    }
    if (get_op() == "COTH")
    {
        return 1 / tanh(number);
    }
    if (get_op() == "ARCCOSH")
    {
        return acosh(number);
    }
    if (get_op() == "ARCSINH")
    {
        return asinh(number);
    }
    if (get_op() == "ARCTANH")
    {
        return atanh(number);
    }
    if (get_op() == "ARCSECH")
    {
        return 1 / acosh(number);
    }
    if (get_op() == "ARCCSCH")
    {
        return 1 / asinh(number);
    }
    if (get_op() == "ARCCOTH")
    {
        return 1 / atanh(number);
    }
    if (get_op() == "LOG")
    {
        return log10(number);
    }
    if (get_op() == "LN")
    {
        return log(number);
    }
    if (get_op() == "SQRT")
    {
        return sqrt(number);
    }
    if (get_op() == "EXP")
    {
        return exp(number);
    }
    if (get_op() == "LOG2")
    {
        return log2(number);
    }
    if (get_op() == "EXP10")
    {
        return pow(10, number);
    }
    if (get_op() == "EXP2")
    {
        return pow(2, number);
    }
    if (get_op() == "CBRT")
    {
        return cbrt(number);
    }
    if (get_op() == "GAMMA")
    {
        return tgamma(number);
    }
    if (get_op() == "ERF")
    {
        return erf(number);
    }
    if (get_op() == "ERFC")
    {
        return erfc(number);
    }
    if (get_op() == "CEIL")
    {
        return ceil(number);
    }

    assert(false && "Function is not of a valid type");

    return 0;
}

int Function::get_prec() const
{
    return 2;
}

TOKEN_TYPES Function::type_of() const
{
    return FUNCTION;
}

ostream &Function::print(ostream &outs) const
{
    outs << get_string();
    return outs;
}

void Function::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of() << endl;
}