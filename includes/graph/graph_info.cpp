#include "graph_info.h"

Graph_Info::Graph_Info()
{
    //deliberately empty
}

Graph_Info::Graph_Info(sf::Vector2f window_dimensions,
                       sf::Vector2f origin,
                       sf::Vector2f domain,
                       sf::Vector2f range,
                       string equation,
                       int points) : _window_dimensions(window_dimensions), _origin(origin), _domain(domain), _range(range), _equation(equation), _points(points) {}