#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "number.h"

using namespace std;

class Variable : public Number
{
public:
    Variable(string var);

    double evaluate(double value) const;

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
    string _var;
};

#endif