#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>

#include "../token/token.h"
#include "../token/operator.h"
#include "../token/number.h"
#include "../token/variable.h"
#include "../token/function.h"
#include "../token/special_function.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

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