#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

const float SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width / 2;
const float SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height / 2;
const float WORK_PANEL = SCREEN_WIDTH * (float(4) / float(5));
const float SIDE_BAR = SCREEN_WIDTH * (float(1) / float(5));

const sf::Vector2f WINDOW_POSITION = sf::Vector2f((SCREEN_WIDTH / 2.5) - WORK_PANEL / 6, (SCREEN_HEIGHT / 2) - WORK_PANEL / 5);
const float MENU_WIDTH = (WORK_PANEL / 3);
const float MENU_HEIGHT = (WORK_PANEL / 2.5);

const int MAX_DOMAIN = 20000;

const int EQUATION_POSITION = 0;

const int DOMAIN_POSITION = 26;
const int SB_MOUSE_POSITION = DOMAIN_POSITION + 1;

const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;

const int CMD_ZOOM_IN = SB_KEY_PRESSED + 1;
const int CMD_ZOOM_OUT = CMD_ZOOM_IN + 1;
const int RESET_GRAPH = CMD_ZOOM_OUT + 1;

const int LEFT_ARROW = RESET_GRAPH + 1;
const int RIGHT_ARROW = LEFT_ARROW + 1;
const int UP_ARROW = RIGHT_ARROW + 1;
const int DOWN_ARROW = UP_ARROW + 1;

const int NEW_FUNCTION = DOWN_ARROW + 1;

enum TOKEN_TYPES
{
    NUMBER,
    OPERATOR,
    VARIABLE,
    FUNCTION,
    SPECIAL_FUNCTION,
    LEFTPAREN,
    RIGHTPAREN
};

#endif // CONSTANTS_H
