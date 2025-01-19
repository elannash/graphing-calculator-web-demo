#include "../include/shunting_yard.h"
#include <iostream>

ShuntingYard::ShuntingYard() {}

ShuntingYard::ShuntingYard(const Queue<Token *> &q) : _infix_q(q) {}

void ShuntingYard::infix(const Queue<Token *> &q)
{
    _infix_q = q;
}

Queue<Token *> ShuntingYard::postfix(const Queue<Token *> &q)
{
    _infix_q = q;

    Queue<Token *> infix_q = _infix_q;
    Queue<Token *> postfix_q;
    Stack<Token *> holding_stack;
    bool previousWasOperatorOrLeftParen = true; // track context for unary

    while (!infix_q.empty())
    {
        Token *current = infix_q.front();
        TOKEN_TYPES type = current->type_of();

        switch (type)
        {
        case NUMBER:
        case VARIABLE:
        {
            postfix_q.push(current);
            previousWasOperatorOrLeftParen = false; // reset unary detection
            break;
        }
        case OPERATOR:
        {
            Operator *op = static_cast<Operator *>(current);

            if (previousWasOperatorOrLeftParen)
            {
                op->set_as_unary();
            }

            while (!holding_stack.empty() &&
                   holding_stack.top()->type_of() != LEFTPAREN &&
                   static_cast<Operator *>(holding_stack.top())->get_prec() >= op->get_prec())
            {
                Token *top = holding_stack.pop();
                postfix_q.push(top);
            }

            holding_stack.push(op);
            previousWasOperatorOrLeftParen = true;
            break;
        }
        case FUNCTION:
        case SPECIAL_FUNCTION:
        {
            holding_stack.push(current);
            previousWasOperatorOrLeftParen = true; // functions expect arguments
            break;
        }
        case LEFTPAREN:
        {
            holding_stack.push(current);
            previousWasOperatorOrLeftParen = true; // new subexpression starts
            break;
        }
        case RIGHTPAREN:
        {
            // resolve operators until left parenthesis is found
            while (!holding_stack.empty() && holding_stack.top()->type_of() != LEFTPAREN)
            {
                Token *top = holding_stack.pop();
                postfix_q.push(top);
            }

            if (!holding_stack.empty() && holding_stack.top()->type_of() == LEFTPAREN)
            {
                holding_stack.pop();
            }
            else
            {
                std::cerr << "Error: Mismatched parentheses.\n";
                return postfix_q;
            }

            // if the top of the stack is a function, pop it to the postfix queue
            if (!holding_stack.empty() &&
                (holding_stack.top()->type_of() == FUNCTION || holding_stack.top()->type_of() == SPECIAL_FUNCTION))
            {
                Token *func = holding_stack.pop();
                postfix_q.push(func);
            }

            previousWasOperatorOrLeftParen = false; // reset context
            break;
        }
        case ARGUMENT_SEPARATOR:
        {
            // resolve operators until a left parenthesis is encountered
            while (!holding_stack.empty() && holding_stack.top()->type_of() != LEFTPAREN)
            {
                Token *top = holding_stack.pop();
                postfix_q.push(top);
            }

            // ensure there is a matching left parenthesis
            if (holding_stack.empty() || holding_stack.top()->type_of() != LEFTPAREN)
            {
                std::cerr << "Error: Argument separator without matching left parenthesis or function.\n";
                return postfix_q;
            }

            previousWasOperatorOrLeftParen = true; // reset unary detection after a comma
            break;
        }
        default:
        {
            std::cerr << "Error: Unknown token type encountered: " << current->get_string() << "\n";
            break;
        }
        }

        infix_q.pop();
    }

    while (!holding_stack.empty())
    {
        Token *top = holding_stack.pop();
        if (top->type_of() == LEFTPAREN)
        {
            std::cerr << "Error: Mismatched parentheses detected at end of input." << std::endl;
        }
        else
        {
            postfix_q.push(top);
        }
    }

    return postfix_q;
}

Queue<Token *> ShuntingYard::postfix()
{
    return postfix(_infix_q);
}
