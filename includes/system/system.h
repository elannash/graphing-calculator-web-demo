#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../graph/graph_info.h"
#include "../graph/graph.h"
#include "../graph/translate_coords.h"

using namespace std;
class System
{
public:
    System(Graph_Info *graph_info);

    void Step(int command);
    void Draw(sf::RenderWindow &window);

private:
    Graph_Info *_graph_info;
    Graph _g;
    sf::CircleShape shape;
};

#endif // SYSTEM_H
