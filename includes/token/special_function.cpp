#include "special_function.h"

SpecialFunction::SpecialFunction(string Token_str) : Function(Token_str) {}

double SpecialFunction::evaluate(double num1, double num2) const
{
    if (get_op() == "MAX")
    {
        return max(num1, num2);
    }
    if (get_op() == "MIN")
    {
        return min(num1, num2);
    }
    if (get_op() == "POW")
    {
        return pow(num1, num2);
    }

    return 0;
}

int SpecialFunction::get_prec() const
{
    return 2;
}

TOKEN_TYPES SpecialFunction::type_of() const
{
    return SPECIAL_FUNCTION;
}

ostream &SpecialFunction::print(ostream &outs) const
{
    outs << get_string();
    return outs;
}

void SpecialFunction::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of() << endl;
}
