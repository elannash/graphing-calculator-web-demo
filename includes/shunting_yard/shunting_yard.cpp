#include "shunting_yard.h"

ShuntingYard::ShuntingYard() {}

ShuntingYard::ShuntingYard(const Queue<Token *> &q) : _infix_q(q) {}

void ShuntingYard::infix(const Queue<Token *> &q)
{
    _infix_q = q;
}

Queue<Token *> ShuntingYard::postfix(const Queue<Token *> &q)
{
    //while loop while infix_q is not empty
    //uses a switch statement in conjunction with the type_of() function to determine the Token at the front of the queue
    //otherwise, follows the general Shunting Yard algorithm

    _infix_q = q;

    Queue<Token *> infix_q = _infix_q;
    Queue<Token *> postfix_q;
    Stack<Token *> holding_stack;

    while (!infix_q.empty())
    {
        int type = infix_q.front()->type_of();

        switch (type)
        {
        case NUMBER:
        {
            postfix_q.push(infix_q.front());

            break;
        }
        case OPERATOR:
        {
            if (!holding_stack.empty())
            {
                if (holding_stack.top()->type_of() == LEFTPAREN)
                {
                    holding_stack.push(infix_q.front());
                }
                else if (static_cast<Operator *>(holding_stack.top())->get_prec() < static_cast<Operator *>(infix_q.front())->get_prec())
                {
                    holding_stack.push(infix_q.front());
                }
                else
                {
                    postfix_q.push(holding_stack.pop());
                    holding_stack.push(infix_q.front());
                }
            }
            else
            {
                holding_stack.push(infix_q.front());
            }

            break;
        }
        case VARIABLE:
        {
            postfix_q.push(infix_q.front());

            break;
        }
        case FUNCTION:
        {
            holding_stack.push(infix_q.front());

            break;
        }
        case SPECIAL_FUNCTION:
        {
            holding_stack.push(infix_q.front());

            break;
        }
        case LEFTPAREN:
        {
            holding_stack.push(infix_q.front());

            break;
        }
        case RIGHTPAREN:
        {
            //pretty ugly in order to solve issue that should be dealt with through error handling

            //if the stack is not empty
            //pop the stack and push into queue until reaching a leftparen
            //check to make sure stack isn't empty to avoid assert
            //if it is empty, break the loop

            //if the holding stack isn't empty at the end, pop leftparen last and throw away

            if (!holding_stack.empty())
            {
                while (holding_stack.top()->type_of() != LEFTPAREN)
                {
                    postfix_q.push(holding_stack.pop());

                    if (holding_stack.empty())
                    {
                        break;
                    }
                }
            }

            if (!holding_stack.empty())
            {
                holding_stack.pop();
            }

            break;
        }
        }

        infix_q.pop();
    }

    while (!holding_stack.empty())
    {
        postfix_q.push(holding_stack.pop());
    }

    return postfix_q;
}

Queue<Token *> ShuntingYard::postfix()
{
    return postfix(_infix_q);
}