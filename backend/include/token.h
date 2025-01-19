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

protected:
    TOKEN_TYPES _type;
    string _token_str;
};

class ErrorToken : public Token
{
public:
    explicit ErrorToken(const string &message)
        : Token(message, ERROR) {}

    string get_string() const override { return "Error: " + _token_str; }
    TOKEN_TYPES type_of() const override { return ERROR; }
    ostream &print(ostream &outs = cout) const override
    {
        outs << "Error: " << _token_str;
        return outs;
    }
};

#endif
