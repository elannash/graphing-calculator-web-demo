#ifndef SPECIAL_FUNCTION_H
#define SPECIAL_FUNCTION_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cmath>
#include "function.h"

class SpecialFunction : public Function
{
public:
    SpecialFunction(string Token_str);
    double evaluate(double num1, double num2) const;
    virtual int get_prec() const; //doesnt really need to be virtual, could stay in operator class

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
};

#endif
