#ifndef TRANSLATE_COORDS_H
#define TRANSLATE_COORDS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "../constants/constants.h"
#include "graph_info.h"

class translate
{
public:
    translate(Graph_Info *graph_info);

    sf::Vector2f translate_point(sf::Vector2f point) const;
    sf::Vector2f operator()(sf::Vector2f point) const;
    
    sf::Vector2f reverse_translate(sf::Vector2i screen_coord) const;

private:
    Graph_Info *_graph_info;
};

#endif