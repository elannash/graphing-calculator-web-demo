#include "rpn.h"

RPN::RPN() {}

RPN::RPN(Queue<Token *> Postfix) : _input_q(Postfix), _fail(false) {}

void RPN::set_input(const Queue<Token *> &q)
{
    _input_q = q;
}

double RPN::evaluate(double value)
{
    Queue<Token *> input_q = _input_q; //copies _input_q to avoid making changes to member q
    Stack<double> output_stack;
    _fail = false;

    while (!input_q.empty())
    {
        int type = input_q.front()->type_of();

        switch (type)
        {
        case NUMBER:
        {
            //casts the token* at the front of the input queue to an number* and then calls get_num to get the double value and pushes it into the output stack

            double result = static_cast<Number *>(input_q.front())->get_num();
            output_stack.push(result);

            break;
        }
        case OPERATOR:
        {
            //casts the token* at the from of the input queue to an operator* and then calls evaluate on the top two popped elements of the stack
            //pushes result back into stack

            if (output_stack.size() == 0) //should be using a set_fail() function but output_stack is not a member of class
            {                             //so it cannot check output_stack size
                _fail = true;
                return 0;
            }

            if (output_stack.size() > 1) //this checks size to see if evaluate should be called on two numbers or just one
            {
                double result = static_cast<Operator *>(input_q.front())->evaluate(output_stack.pop(), output_stack.pop());
                output_stack.push(result);
            }
            else
            {
                double result = static_cast<Operator *>(input_q.front())->evaluate(output_stack.pop());
                output_stack.push(result);
            }

            break;
        }
        case VARIABLE:
        {
            //casts the token* at the front of the input queue to a variable* and then calls evaluate
            //pushes result from evaluate into output stack

            double result = static_cast<Variable *>(input_q.front())->evaluate(value);
            output_stack.push(result);

            break;
        }
        case FUNCTION:
        {
            //casts the token* at the front of the input queue to a function*
            //then evals and pushes back into stack

            if (output_stack.size() == 0) //should be using a set_fail() function but output_stack is not a member of class
            {                             //so it cannot check output_stack size
                _fail = true;
                return 0;
            }

            double result = static_cast<Function *>(input_q.front())->evaluate(output_stack.pop());
            output_stack.push(result);

            break;
        }
        case SPECIAL_FUNCTION:
        {
            //casts the token* at the front of the input queue to a specialfunction*
            //then evals and pushes back into stack

            if (output_stack.size() < 2) //should be using a set_fail() function but output_stack is not a member of class
            {                            //so it cannot check output_stack size
                _fail = true;
                return 0;
            }

            double result = static_cast<SpecialFunction *>(input_q.front())->evaluate(output_stack.pop(), output_stack.pop());
            output_stack.push(result);

            break;
        }
        }

        input_q.pop();
    }

    if (output_stack.size() != 1) //should be using a set_fail() function but output_stack is not a member of class
    {                             //so it cannot check output_stack size
        _fail = true;
        return 0;
    }

    //assert(output_stack.size() == 1 && "output_stack should have exactly one element");

    return output_stack.pop();
}

double RPN::operator()(double value)
{
    return evaluate(value);
}

bool RPN::fail() const
{
    return _fail;
}