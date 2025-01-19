#include "../include/graph_info.h"
#include <emscripten/bind.h>

Graph_Info::Graph_Info()
    : _window_dimensions({0, 0}), _origin({0, 0}),
      _domain({-10, 10}), _range({-10, 10}),
      _equation(""), _points(1000) {}

Graph_Info::Graph_Info(std::pair<float, float> window_dimensions, std::pair<float, float> origin,
                       std::pair<float, float> domain, std::pair<float, float> range,
                       std::string equation, int points)
    : _window_dimensions(window_dimensions), _origin(origin),
      _domain(domain), _range(range),
      _equation(equation), _points(points) {}

// expose Graph_Info class to webassembly
EMSCRIPTEN_BINDINGS(graph_info_bindings) {
    emscripten::class_<Graph_Info>("Graph_Info")
        .constructor<>()
        .constructor<std::pair<float, float>, std::pair<float, float>,
                     std::pair<float, float>, std::pair<float, float>,
                     std::string, int>()
        .property("window_dimensions", &Graph_Info::_window_dimensions)
        .property("origin", &Graph_Info::_origin)
        .property("domain", &Graph_Info::_domain)
        .property("range", &Graph_Info::_range)
        .property("equation", &Graph_Info::_equation)
        .property("points", &Graph_Info::_points);
}
