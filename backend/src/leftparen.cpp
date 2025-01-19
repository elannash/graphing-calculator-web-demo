#include "../include/leftparen.h"

LeftParen::LeftParen() : Token("(", LEFTPAREN) {}

TOKEN_TYPES LeftParen::type_of() const
{
    return LEFTPAREN;
}

ostream &LeftParen::print(ostream &outs) const
{
    outs << "(";
    return outs;
}

void LeftParen::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of();
}