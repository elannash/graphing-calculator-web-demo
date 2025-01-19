#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

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