#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

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

class ShuntingYard
{
public:
    ShuntingYard();
    ShuntingYard(const Queue<Token *> &q);

    void infix(const Queue<Token *> &q); //mutator

    Queue<Token *> postfix(const Queue<Token *> &q); //this will also store q in _infix_q
    Queue<Token *> postfix();

private:
    Queue<Token *> _infix_q;
};

#endif