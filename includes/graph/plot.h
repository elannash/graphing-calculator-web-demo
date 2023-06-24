#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graph_info.h"
#include "../tokenizer/tokenizer.h"
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../token/variable.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/number.h"
#include "../token/special_function.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "translate_coords.h"

class Plot
{
public:
    Plot(Graph_Info *graph_info);

    Vector<sf::Vector2f> get_points();
    Vector<sf::Vector2f> operator()();

private:
    Graph_Info *_graph_info;
    Queue<Token *> _post_fix_q;
};

#endif /* PLOT_H */
