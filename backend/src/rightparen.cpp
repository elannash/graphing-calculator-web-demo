#include "../include/rightparen.h"

RightParen::RightParen() : Token(")", RIGHTPAREN) {}

TOKEN_TYPES RightParen::type_of() const
{
    return RIGHTPAREN;
}

ostream &RightParen::print(ostream &outs) const
{
    outs << ")";
    return outs;
}

void RightParen::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of();
}