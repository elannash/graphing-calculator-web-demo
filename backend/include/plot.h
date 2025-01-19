#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <vector>
#include <utility>
#include "graph_info.h"
#include "tokenizer.h"
#include "MyQueue.h"
#include "token.h"
#include "variable.h"
#include "operator.h"
#include "shunting_yard.h"
#include "rpn.h"
#include "vector_class.h"

class Plot
{
public:
    Plot(Graph_Info *graph_info);

    Vector<std::pair<float, float>> get_points();             // internal method using custom Vector
    Vector<std::pair<float, float>> operator()();             // pperator overload using custom Vector
    std::vector<std::pair<float, float>> generate_points();   // exposed method for WebAssembly

private:
    Graph_Info *_graph_info;       // graph configuration
    Queue<Token *> _post_fix_q;    // postfix queue for rpn evaluation
};

#endif /* PLOT_H */
