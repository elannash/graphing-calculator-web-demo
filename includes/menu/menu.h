#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../constants/constants.h"

//very basic menu class
class Menu
{
public:
    Menu(sf::Vector2f position, float width, float height);

    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);
    void draw(sf::RenderWindow &window);

    void set_open(bool open);
    bool is_open();

private:
    sf::RectangleShape _rect;

    float _width, _height;
    vector<string> items; //strings to place on the menu
    
    sf::Vector2f _position;
    sf::Color _color;
    sf::Font font;
    sf::Text menu_text;

    bool _open;
};

#endif /* MENU_H */
