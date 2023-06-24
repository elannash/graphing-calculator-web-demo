#include "menu.h"

Menu::Menu(sf::Vector2f position, float width, float height) : _open(false), _position(position), _width(width), _height(height)
{
    items.reserve(15);

    items.push_back("============MENU============");
    items.push_back("");
    items.push_back("ENTER FUNCTION MODE: ENTER / F");
    items.push_back("EXIT FUNCTION MODE: ENTER / ESC");
    items.push_back("");
    items.push_back("SELECT FUNCTION: LEFT CLICK BOX");
    items.push_back("SAVE FUNCTION: RIGHT CLICK BOX");
    items.push_back("");
    items.push_back("ZOOM: SCROLL UP / SCROLL DOWN");
    items.push_back("PAN: ARROW KEYS");
    items.push_back("RESET DOMAIN: R");
    items.push_back("");
    items.push_back("SAVE TO FILE: S WHILE IN MENU");
    items.push_back("LOAD FROM FILE: L WHILE IN MENU");
    items.push_back("");
    items.push_back("CLOSE MENU: F1 / ESC");

    _rect.setPosition(_position);
    _rect.setSize(sf::Vector2f(width, height));
    _rect.setFillColor(sf::Color::White);
    _rect.setOutlineThickness(2);
    _rect.setOutlineColor(sf::Color(153, 153, 153));

    if (!font.loadFromFile("Calibri Regular.ttf"))
    {
        cout << "Menu() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    menu_text.setFont(font);
    menu_text.setCharacterSize(20);
    menu_text.setStyle(sf::Text::Bold);
    menu_text.setFillColor(sf::Color::Black);
    menu_text.setString("============MENU============");
}

void Menu::setPosition(sf::Vector2f position)
{
    _rect.setPosition(position);
}
void Menu::setColor(sf::Color color)
{
    _rect.setFillColor(color);
}
void Menu::draw(sf::RenderWindow &window)
{
    window.draw(_rect);

    const double VERTICAL_LINE_SPACING = 5;
    double LEFT_MARGIN;
    float height = WINDOW_POSITION.y;

    for (vector<string>::iterator it = items.begin(); it != items.end(); it++)
    {
        menu_text.setString(it->c_str());
        LEFT_MARGIN = _width / 2 - menu_text.getLocalBounds().width / 2;
        menu_text.setPosition(sf::Vector2f(_position.x + LEFT_MARGIN, height));
        height += menu_text.getCharacterSize() + VERTICAL_LINE_SPACING;
        window.draw(menu_text);
    }
}
void Menu::set_open(bool open)
{
    _open = open;
}

bool Menu::is_open()
{
    return _open;
}