#include "../include/plot.h"
#include <emscripten/bind.h>
#include <emscripten.h>

Plot::Plot(Graph_Info *graph_info) : _graph_info(graph_info) {}

// internal method: generate graph points using custom Vector
Vector<std::pair<float, float>> Plot::get_points()
{
    Vector<std::pair<float, float>> points; 
    Tokenizer tokenizer(_graph_info->_equation);
    Queue<Token *> infix = tokenizer(); // tokenizer returns a queue of tokens
    ShuntingYard sy(infix);

    _post_fix_q = sy.postfix();

    RPN rpn(_post_fix_q);

    // divide the domain by the number of points to calculate the horizontal distance
    double delta = (_graph_info->_domain.second - _graph_info->_domain.first) / _graph_info->_points;

    // generate graph-space (x, y) points
    for (double i = _graph_info->_domain.first; i <= _graph_info->_domain.second; i += delta)
    {
        points.push_back(std::make_pair(i, rpn(i))); // use rpn to evaluate the y-value for each x
    }

    return points;
}

Vector<std::pair<float, float>> Plot::operator()()
{
    return get_points();
}

// exposed method: convert custom Vector to std::vector
std::vector<std::pair<float, float>> Plot::generate_points() {
    // std::cout << "Entering generate_points with equation: " << _graph_info->_equation << std::endl;

    Vector<std::pair<float, float>> internal_points = get_points();
    std::vector<std::pair<float, float>> output_points;

    for (size_t i = 0; i < internal_points.size(); ++i) {
        auto point = internal_points[i];
        output_points.push_back(point);
        // std::cout << "Generated Point: x = " << point.first << ", y = " << point.second << std::endl;
    }

    // std::cout << "Exiting generate_points. Total points: " << output_points.size() << std::endl;
    return output_points;
}

// expose the plot class and methods to webassembly
EMSCRIPTEN_BINDINGS(plot_bindings)
{
    emscripten::class_<Plot>("Plot")
        .constructor<Graph_Info *>()                          // expose constructor
        .function("generate_points", &Plot::generate_points); // expose generate_points
}
