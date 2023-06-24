#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "../vector/vector_class.h"
#include "../constants/constants.h"

using namespace std;

struct Graph_Info
{
    Graph_Info();
    Graph_Info(sf::Vector2f window_dimensions, sf::Vector2f origin, sf::Vector2f domain, sf::Vector2f range, string equation, int points);

    sf::Vector2f _window_dimensions;
    sf::Vector2f _origin;
    sf::Vector2f _domain;
    sf::Vector2f _range;

    string _equation;
    int _points;
};

#endif /* GRAPH_INFO_H */
