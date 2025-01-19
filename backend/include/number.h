#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "token.h"

using namespace std;

class Number : public Token
{
public:
    Number(double num);
    Number(string num);

    virtual TOKEN_TYPES type_of() const;
    virtual ostream &print(ostream &outs = cout) const;
    virtual void info() const;

    void set_num(double num);
    double get_num() const;

private:
    double _num;
};

typedef Number Integer; //for basic_test

#endif