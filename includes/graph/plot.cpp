#include "plot.h"

Plot::Plot(Graph_Info *graph_info) : _graph_info(graph_info) {}

Vector<sf::Vector2f> Plot::get_points()
{
    Vector<sf::Vector2f> points; //declaring the Vector of points that will be returned
    Tokenizer tokenizer(_graph_info->_equation);
    Queue<Token *> infix = tokenizer(); //tokenizer () operator returns a queue of tokens
    ShuntingYard sy(infix);

    _post_fix_q = sy.postfix();

    RPN rpn(_post_fix_q);

    translate translator(_graph_info);

    //dividing the entire domain by the number of points to get the horizontal distance between points
    double delta = (_graph_info->_domain.y - _graph_info->_domain.x) / _graph_info->_points;

    //this loop pushes back the translated (x,y) point
    for (double i = _graph_info->_domain.x; i <= _graph_info->_domain.y; i += delta)
    {
        points.push_back(translator(sf::Vector2f(i, rpn(i))));
    }

    /*
    //this isn't actually getting called because i'm handling errors poorly in my rpn class
    //will fix at some point
    if(rpn.fail())
    {
        points.clear();
    }*/

    return points;
}

Vector<sf::Vector2f> Plot::operator()()
{
    return get_points();
}