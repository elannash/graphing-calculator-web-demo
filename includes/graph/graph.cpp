#include "graph.h"

Graph::Graph(Graph_Info *graph_info) : _plotter(graph_info), _graph_info(graph_info) {}

void Graph::draw(sf::RenderWindow &window, sf::CircleShape &shape) const
{
    //loops through points vector and draws circle at that position
    //calls draw_axes

    for (int i = 0; i < _points.size(); i++)
    {
        shape.setPosition(_points[i]);
        window.draw(shape);
    }

    draw_axes(window, shape);
}

void Graph::draw_axes(sf::RenderWindow &window, sf::CircleShape &shape) const
{
    Vector<sf::Vector2f> points;
    translate translator(_graph_info);

    float delta = 10 * (_graph_info->_domain.y - _graph_info->_domain.x) / _graph_info->_points; //arbitrary delta (distance between points)

    //x-axis
    //pushes points into vector after translating
    for (float i = _graph_info->_domain.x; i <= _graph_info->_domain.y; i += delta)
    {
        points.push_back(translator(sf::Vector2f(i, 0)));
    }

    //y-axis
    //pushes points into vector after translating
    for (float i = _graph_info->_range.x; i <= _graph_info->_range.y; i += delta)
    {
        points.push_back(translator(sf::Vector2f(0, i)));
    }

    //drawing
    for (int i = 0; i < points.size(); i++)
    {
        shape.setPosition(points[i]);
        window.draw(shape);
    }
}

void Graph::update()
{
    _points = _plotter();
}