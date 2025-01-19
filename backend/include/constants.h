#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

// token types for equation parsing
enum TOKEN_TYPES
{
    NUMBER,
    OPERATOR,
    VARIABLE,
    FUNCTION,
    SPECIAL_FUNCTION,
    LEFTPAREN,
    RIGHTPAREN,
    ARGUMENT_SEPARATOR
};

#endif // CONSTANTS_H
