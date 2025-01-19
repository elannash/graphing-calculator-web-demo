#ifndef ARGUMENT_SEPARATOR_H
#define ARGUMENT_SEPARATOR_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "token.h"

class ArgumentSeparator : public Token
{
public:
    ArgumentSeparator() : Token(",", ARGUMENT_SEPARATOR) {}

    virtual string get_string() const override { return ","; }
    virtual TOKEN_TYPES type_of() const override { return ARGUMENT_SEPARATOR; }

    virtual ostream &print(ostream &outs = cout) const override
    {
        outs << "[ArgumentSeparator: ,]";
        return outs;
    }
};

#endif /* ARGUMENT_SEPARATOR_H */