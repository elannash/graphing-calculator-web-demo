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

    virtual double evaluate(double lhs, double rhs) const;
    double evaluate(double unary) const;

    virtual int get_prec() const;
    void set_prec(int precedence);

    void set_as_unary();
    bool is_unary() const;

    string get_op() const;

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

private:
    string _op;
    int _precedence;
    bool _isUnary;
};

#endif
