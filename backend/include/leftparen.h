#ifndef LEFT_PAREN_H
#define LEFT_PAREN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "token.h"

class LeftParen : public Token
{
public:
    LeftParen();

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
};

#endif