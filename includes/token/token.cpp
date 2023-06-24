#include "token.h"

Token::Token(string Token_str, TOKEN_TYPES type) : _token_str(Token_str), _type(type) {}

TOKEN_TYPES Token::type_of() const
{
    return _type;
}

string Token::get_string() const
{
    return _token_str;
}

ostream &Token::print(ostream &outs) const
{
    return outs;
}

void Token::info() const
{
    cout << "TOKENS: "
         << "\t"
         << "TYPE: " << endl
         << "NUMBER: "
         << "\t"
         << NUMBER << endl
         << "OPERATOR: "
         << "\t" << OPERATOR << endl
         << "VARIABLE: "
         << "\t" << VARIABLE << endl
         << "FUNCTION: "
         << "\t" << FUNCTION << endl
         << "LEFTPAREN: "
         << "\t" << LEFTPAREN << endl
         << "RIGHTPAREN: "
         << "\t" << RIGHTPAREN << endl;
}

ostream &operator<<(ostream &outs, const Token &token)
{
    token.print(outs);
    return outs;
}

ostream &operator<<(ostream &outs, const Token *token_ptr)
{
    token_ptr->print(outs);
    return outs;
}