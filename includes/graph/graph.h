#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "graph_info.h"
#include "plot.h"
#include "../token/variable.h"
#include "../token/Operator.h"
#include "../token/number.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"

class Graph
{
public:
    Graph(Graph_Info *graph_info);

    void update();
    void draw(sf::RenderWindow &window, sf::CircleShape &shape) const;
    void draw_axes(sf::RenderWindow &window, sf::CircleShape &shape) const; //could be private

private:
    Graph_Info *_graph_info;
    Plot _plotter;

    Vector<sf::Vector2f> _points;
};

#endif /* GRAPH_H */
