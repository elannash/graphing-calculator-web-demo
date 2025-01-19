#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include "token.h"

class Variable : public Token
{
public:
    Variable(std::string var);

    virtual TOKEN_TYPES type_of() const override;
    virtual std::string get_string() const override;
    virtual std::ostream &print(std::ostream &outs = std::cout) const override;
    virtual void info() const override;

    double evaluate(double value) const;

private:
    std::string _var;
};

#endif
