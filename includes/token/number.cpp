#include "number.h"

Number::Number(double num) : Token(to_string(num), NUMBER), _num(num) {}
Number::Number(string num) : Token(num, NUMBER), _num(stoi(num)) {}

TOKEN_TYPES Number::type_of() const
{
    return NUMBER;
}

void Number::set_num(double num)
{
    _num = num;
}

double Number::get_num() const
{
    return _num;
}

ostream &Number::print(ostream &outs) const
{
    // outs << fixed << showpoint;
    // outs << setprecision(2);
    outs << _num;

    return outs;
}

void Number::info() const
{
    cout << "TOKEN: " << get_string() << endl
         << "TYPE: " << type_of() << endl
         << "VALUE: " << _num;
}