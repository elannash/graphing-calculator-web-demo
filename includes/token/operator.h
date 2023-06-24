#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cmath>
#include "token.h"

using namespace std;

class Operator : public Token
{
public:
    Operator(string Token_str);

    virtual double evaluate(double lhs, double rhs) const; //virtual so functinos class can define its own stuff
    double evaluate(double unary) const;
    virtual int get_prec() const; //this doesn't really need to be virtual
    string get_op() const;

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
    string _op;
    int _precedence;
};

#endif