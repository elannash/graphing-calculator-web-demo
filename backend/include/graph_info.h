#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <iostream>
#include <utility> // for std::pair
#include <string>

struct Graph_Info
{
    Graph_Info();
    Graph_Info(std::pair<float, float> window_dimensions, std::pair<float, float> origin,
               std::pair<float, float> domain, std::pair<float, float> range,
               std::string equation, int points);

    std::pair<float, float> _window_dimensions; // width and height of the window
    std::pair<float, float> _origin;            // origin of the graph
    std::pair<float, float> _domain;            // x-axis range
    std::pair<float, float> _range;             // y-axis range

    std::string _equation; // equation string
    int _points;           // number of points to plot
};

#endif /* GRAPH_INFO_H */
