#include "variable.h"

Variable::Variable(string var) : Number(0), _var(var) {}

double Variable::evaluate(double value) const
{
    return value;
}

TOKEN_TYPES Variable::type_of() const
{
    return VARIABLE;
}

ostream &Variable::print(ostream &outs) const
{
    outs << _var;
    return outs;
}

void Variable::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of() << endl
         << "VARIABLE: " << _var;
}