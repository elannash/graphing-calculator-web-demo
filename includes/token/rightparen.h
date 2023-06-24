#ifndef RIGHT_PAREN_H
#define RIGHT_PAREN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "token.h"

class RightParen : public Token
{
public:
    RightParen();

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
};

#endif