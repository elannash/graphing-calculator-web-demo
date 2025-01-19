#include "../include/rpn.h"
#include <iostream>

RPN::RPN() {}

RPN::RPN(Queue<Token *> Postfix) : _input_q(Postfix), _fail(false) {}

void RPN::set_input(const Queue<Token *> &q)
{
    _input_q = q;
}

double RPN::evaluate(double value)
{
    Queue<Token *> input_q = _input_q;
    Stack<double> output_stack;
    _fail = false;

    while (!input_q.empty())
    {
        Token *current_token = input_q.front();
        int type = current_token->type_of();

        switch (type)
        {
        case NUMBER:
        {
            double result = static_cast<Number *>(current_token)->get_num();
            output_stack.push(result);
            break;
        }
        case OPERATOR:
        {
            Operator *op = static_cast<Operator *>(current_token);

            if (op->is_unary())
            {
                if (output_stack.empty())
                {
                    _fail = true;
                    std::cerr << "Error: Stack is empty for unary operator." << std::endl;
                    return 0;
                }
                double operand = output_stack.pop();
                double result = op->evaluate(operand);
                output_stack.push(result);
            }
            else
            {
                if (output_stack.size() < 2)
                {
                    _fail = true;
                    std::cerr << "Error: Insufficient arguments for binary operator." << std::endl;
                    return 0;
                }

                double rhs = output_stack.pop();
                double lhs = output_stack.pop();
                double result = op->evaluate(lhs, rhs);
                output_stack.push(result);
            }
            break;
        }
        case VARIABLE:
        {
            double result = static_cast<Variable *>(current_token)->evaluate(value);
            output_stack.push(result);
            break;
        }
        case FUNCTION:
        {
            if (output_stack.size() < 1)
            {
                _fail = true;
                std::cerr << "Error: Stack is empty for FUNCTION." << std::endl;
                return 0;
            }

            double arg = output_stack.pop();
            double result = static_cast<Function *>(current_token)->evaluate(arg);
            output_stack.push(result);
            break;
        }
        case SPECIAL_FUNCTION:
        {
            if (output_stack.size() < 2)
            {
                _fail = true;
                std::cerr << "Error: Insufficient arguments for SPECIAL_FUNCTION." << std::endl;
                std::cerr << "Stack state at error: ";
                for (const auto &val : output_stack)
                {
                    std::cerr << val << " ";
                }
                std::cerr << std::endl;
                return 0;
            }

            double right = output_stack.pop();
            double left = output_stack.pop();
            double result = static_cast<SpecialFunction *>(current_token)->evaluate(left, right);

            output_stack.push(result);
            break;
        }
        default:
            std::cerr << "Unknown token type encountered: " << type << std::endl;
            _fail = true;
            return 0;
        }

        input_q.pop();
    }

    if (output_stack.size() != 1)
    {
        _fail = true;
        std::cerr << "Error: Stack does not contain exactly one element after evaluation. Stack size: " << output_stack.size() << std::endl;
        return 0;
    }

    double final_result = output_stack.pop();
    return final_result;
}

double RPN::operator()(double value)
{
    return evaluate(value);
}

bool RPN::fail() const
{
    return _fail;
}
