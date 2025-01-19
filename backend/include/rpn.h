#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>

#include "token.h"
#include "operator.h"
#include "number.h"
#include "variable.h"
#include "function.h"
#include "special_function.h"
#include "leftparen.h"
#include "rightparen.h"

#include "MyQueue.h"
#include "MyStack.h"

using namespace std;

class RPN
{
public:
    RPN();
    RPN(Queue<Token *> Postfix);

    void set_input(const Queue<Token *> &q);

    double evaluate(double value = 0);
    double operator()(double value = 0);
    bool fail() const;

private:
    Queue<Token *> _input_q;
    bool _fail;
};

#endif