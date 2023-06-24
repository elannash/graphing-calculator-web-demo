#include "translate_coords.h"

translate::translate(Graph_Info *graph_info) : _graph_info(graph_info) {}

sf::Vector2f translate::translate_point(sf::Vector2f point) const
{
    //value for the entire domain (x2-x1)
    float total_domain = _graph_info->_domain.y - _graph_info->_domain.x;

    //work_panel is used instead of screen_width & screen_height to maintain a perfect square
    //doubles i & j give the unit vector determined by the screen size and domain
    float i = _graph_info->_origin.x + (WORK_PANEL / total_domain);
    float j = _graph_info->_origin.y - (WORK_PANEL / total_domain);
    sf::Vector2f basis(i, j); //unit vector aka basis vector

    sf::Vector2f screen_coord; //resulting point being returned

    screen_coord.x = _graph_info->_origin.x + (point.x * (basis.x - _graph_info->_origin.x));
    screen_coord.y = _graph_info->_origin.y + (point.y * (basis.y - _graph_info->_origin.y));

    //these if statements prevent erroneous coordinates from being returned (coords that are negative or out of bounds)
    //this is probably a terrible way to handle this issue
    //also some coords are still printed off screen since WORK_PANEL is larger than screen height, could not figure out a way to fix this issue mathematically
    //opted not to use these, sfml can handle out of bounds coords
    /*if (result.y < 0 || result.y > WORK_PANEL)
    {
        return sf::Vector2f(0, 0);
    }
    if (result.x < 0 || result.x > WORK_PANEL)
    {
        return sf::Vector2f(0, 0);
    }*/

    return screen_coord;
}

sf::Vector2f translate::operator()(sf::Vector2f point) const
{
    return translate_point(point);
}

sf::Vector2f translate::reverse_translate(sf::Vector2i screen_coord) const
{
    //this function is very similar to the translate_point() function
    //i used the same equation as above, but just solved for point

    float total_domain = _graph_info->_domain.y - _graph_info->_domain.x;

    float i = _graph_info->_origin.x + (WORK_PANEL / total_domain);
    float j = _graph_info->_origin.y - (WORK_PANEL / total_domain);
    sf::Vector2f basis(i, j);

    sf::Vector2f point;

    point.x = (screen_coord.x-_graph_info->_origin.x)/(basis.x-_graph_info->_origin.x);
    point.y = (screen_coord.y-_graph_info->_origin.y)/(basis.y-_graph_info->_origin.y);

    return point;
}