#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "../system/system.h"
#include "../sidebar/sidebar.h"
#include "../constants/constants.h"
#include "../tokenizer/tokenizer.h"
#include "../menu/menu.h"

class animate
{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
    bool save(const char fname[], const vector<string> &list);
    bool load(const char fname[], vector<string> &list);

    string mouse_pos_string(sf::RenderWindow &window);

private:
    Graph_Info *_graph_info;

    System system; //container for all the animated objects
    Sidebar sidebar;
    Menu menu;

    sf::RenderWindow window;

    sf::Font font;       //font to draw on main screen
    sf::Text help_label; //text to draw on main screen
    sf::Text function_input_label;
    sf::Text function_label;

    //rectangular message sidebar
    sf::CircleShape mousePoint;                             //The little red dot
    sf::RectangleShape invis_rectangles[SB_MOUSE_POSITION]; //sb_mouse_position is the last position on the sidebar, so only create array of that size

    bool mouseIn;       //mouse is in the screen
    bool function_mode; //boolean for function input mode

    int command; //command to send to system

    string filename;
};

#endif // GAME_H