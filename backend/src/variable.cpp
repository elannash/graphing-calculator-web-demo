#include "../include/variable.h"

Variable::Variable(std::string var) : Token(var, VARIABLE), _var(var) {}

TOKEN_TYPES Variable::type_of() const
{
    return VARIABLE;
}

std::string Variable::get_string() const
{
    return _var;
}

std::ostream &Variable::print(std::ostream &outs) const
{
    outs << _var;
    return outs;
}

void Variable::info() const
{
    std::cout << "TOKEN: " << get_string() << std::endl
              << "TYPE: " << type_of() << std::endl
              << "VARIABLE NAME: " << _var << std::endl;
}

double Variable::evaluate(double value) const
{
    return value;
}
