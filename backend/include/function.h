#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cmath>
#include "operator.h"

using namespace std;

class Function : public Operator
{
public:
    Function(string Token_str);

    virtual double evaluate(double number) const;
    virtual int get_prec() const; //doesnt really need to be virtual, could stay in operator class

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
};

#endif
