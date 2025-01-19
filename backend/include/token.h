#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "constants.h"

using namespace std;

class Token
{
public:
    Token(string Token_str, TOKEN_TYPES type);

    virtual string get_string() const;

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

    friend ostream &operator<<(ostream &outs, const Token &token);
    friend ostream &operator<<(ostream &outs, const Token *token_ptr);

private:
    TOKEN_TYPES _type;
    string _token_str;
};

#endif