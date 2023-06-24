#include "system.h"

System::System(Graph_Info *graph_info) : _g(graph_info), _graph_info(graph_info)
{
    shape = sf::CircleShape(0.5);
    shape.setFillColor(sf::Color(153, 153, 153));
}

void System::Step(int command)
{
    translate coord_translator(_graph_info);

    switch (command)
    {
    case CMD_ZOOM_OUT:
    {
        //increases domain and f by a factor of 1.2
        //value arbitrary and can be changed
        //MAX_DOMAIN employed because weird stuff starts happening when the numbers get too big
        //although i'm still not sure why that's the case

        if (_graph_info->_domain.y - _graph_info->_domain.x < MAX_DOMAIN)
        {
            _graph_info->_domain.x *= float(6) / float(5);
            _graph_info->_domain.y *= float(6) / float(5);
            _graph_info->_range.x *= float(6) / float(5);
            _graph_info->_range.y *= float(6) / float(5);

            _g.update();
        }
        break;
    }
    case CMD_ZOOM_IN:
    {
        //decreases domain and range by a factor of ~ 0.84 (inverse of 1.2)
        //value arbitrary and can be changed

        _graph_info->_domain.x *= float(5) / float(6);
        _graph_info->_domain.y *= float(5) / float(6);
        _graph_info->_range.x *= float(5) / float(6);
        _graph_info->_range.y *= float(5) / float(6);

        _g.update();
        break;
    }
    case LEFT_ARROW:
    {
        //calculates one tenth of total domain to keep pan consistent no matter the zoom level
        //origin gets shifted to the RIGHT by one tenth of the work panel (graph area)

        float pan_this_much = float(0.1) * (_graph_info->_domain.y - _graph_info->_domain.x);

        _graph_info->_origin.x += WORK_PANEL * float(0.1);
        _graph_info->_domain.x -= pan_this_much;
        _graph_info->_domain.y -= pan_this_much;

        _g.update();
        break;
    }
    case RIGHT_ARROW:
    {
        //calculates one tenth of total domain to keep pan consistent no matter the zoom level
        //origin gets shifted to the LEFT by one tenth of the work panel (graph area)

        float pan_this_much = float(0.1) * (_graph_info->_domain.y - _graph_info->_domain.x);

        _graph_info->_origin.x -= WORK_PANEL * float(0.1);
        _graph_info->_domain.x += pan_this_much;
        _graph_info->_domain.y += pan_this_much;

        _g.update();
        break;
    }
    case UP_ARROW:
    {
        //calculates one tenth of total range to keep pan consistent no matter the zoom level
        //origin gets shifted UP by one tenth of the work panel (graph area)

        float pan_this_much = float(0.1) * (_graph_info->_range.y - _graph_info->_range.x);

        _graph_info->_origin.y += WORK_PANEL * float(0.1);
        _graph_info->_range.x += pan_this_much;
        _graph_info->_range.y += pan_this_much;

        _g.update();
        break;
    }
    case DOWN_ARROW:
    {
        //calculates one tenth of total range to keep pan consistent no matter the zoom level
        //origin gets shifted DOWN by one tenth of the work panel (graph area)

        float pan_this_much = float(0.1) * (_graph_info->_range.y - _graph_info->_range.x);

        _graph_info->_origin.y -= WORK_PANEL * float(0.1);
        _graph_info->_range.x -= pan_this_much;
        _graph_info->_range.y -= pan_this_much;

        _g.update();
        break;
    }
    case RESET_GRAPH:
    {
        _graph_info->_domain = sf::Vector2f(-6, 6);
        _graph_info->_range = sf::Vector2f(-6, 6);
        _graph_info->_origin = sf::Vector2f(SCREEN_WIDTH / 2.5, SCREEN_HEIGHT / 2);

        _g.update();
        break;
    }
    case NEW_FUNCTION:
    {
        _g.update();

        break;
    }
    default:
        break;
    }
}

void System::Draw(sf::RenderWindow &window)
{
    _g.draw(window, shape);
}
