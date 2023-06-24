#include "animate.h"

using namespace std;

animate::animate() : sidebar(WORK_PANEL, SIDE_BAR), system(_graph_info), command(NEW_FUNCTION), menu(WINDOW_POSITION, MENU_WIDTH, MENU_HEIGHT)
{
    cout << "Animate CTOR: TOP" << endl;

    //
    //
    //

    cout << "Instantiating _graph_info." << endl;

    //declaring Graph_Info
    //and setting values for member variables

    _graph_info = new Graph_Info(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT),
                                 sf::Vector2f(SCREEN_WIDTH / 2.5, SCREEN_HEIGHT / 2),
                                 sf::Vector2f(-6, 6),
                                 sf::Vector2f(-6, 6),
                                 "",
                                 25000);

    cout << "_graph_info instantiated successfully" << endl;

    //
    //
    //

    system = System(_graph_info); //this is needed because _graph_info is changed after initialization list

    //
    //
    //

    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sad graphing calculator");
    window.setFramerateLimit(30);

    mouseIn = false;
    mousePoint = sf::CircleShape();
    mousePoint.setRadius(2.0);
    mousePoint.setFillColor(sf::Color::Red);

    //
    //
    //

    function_mode = false;

    //
    //
    //

    cout << "Animate CTOR. preparing to load the font." << endl;

    if (!font.loadFromFile("../Calibri Regular.ttf"))
    {
        cout << "Animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    help_label = sf::Text("Press F1 For Menu", font);
    help_label.setCharacterSize(20);
    help_label.setStyle(sf::Text::Bold);
    help_label.setFillColor(sf::Color::Black);
    help_label.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - help_label.getCharacterSize() - 10));

    function_input_label = sf::Text("Function Input: Off", font);
    function_input_label.setCharacterSize(20);
    function_input_label.setStyle(sf::Text::Bold);
    function_input_label.setFillColor(sf::Color::Black);
    function_input_label.setPosition(sf::Vector2f(WORK_PANEL - function_input_label.getLocalBounds().width - 10, SCREEN_HEIGHT - function_input_label.getCharacterSize() - 10));

    function_label = sf::Text("asldfjkla;sdk", font);
    function_label.setCharacterSize(20);
    function_label.setStyle(sf::Text::Bold);
    function_label.setFillColor(sf::Color::Black);
    function_label.setPosition(sf::Vector2f(WORK_PANEL - function_label.getLocalBounds().width - 10, function_label.getCharacterSize()));

    cout << "Animate instantiated successfully." << endl;

    //
    //
    //

    //initializing invisible rectangles for sidebar interaction
    float height = 0;
    float vertical_line_spacing = 25; //this is the height of a character + space between boxes
    float width = SCREEN_WIDTH - WORK_PANEL;

    //using DOMAIN_POSITION - 1 to avoid printing over domain or mouse position
    for (int i = 0; i < DOMAIN_POSITION - 1; i++)
    {
        invis_rectangles[i].setPosition(sf::Vector2f(WORK_PANEL, height));
        invis_rectangles[i].setSize(sf::Vector2f(width, vertical_line_spacing));
        invis_rectangles[i].setFillColor(sf::Color::Transparent);
        invis_rectangles[i].setOutlineColor(sf::Color(99, 153, 203));
        invis_rectangles[i].setOutlineThickness(0.5);
        height += vertical_line_spacing;
    }

    //
    //
    //

    //setting menu color
    menu.setColor(sf::Color(99, 153, 203)); //blue

    //
    //
    //

    //setting name for save/load file and loading in any existing items
    filename = "funcs.txt";
    load(filename.c_str(), sidebar.get_items());

    //
    //
    //
}

void animate::Draw()
{
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);

    //drawing sidebar
    sidebar.draw(window);

    //drawing invisible rectangles for sidebar
    for (int i = 0; i < SB_MOUSE_POSITION; i++)
    {
        window.draw(invis_rectangles[i]);
    }

    //drawing the text labels
    window.draw(help_label);
    window.draw(function_input_label);
    window.draw(function_label);

    if (menu.is_open())
    {
        menu.draw(window);
    }

    //drawing mousepoint
    if (mouseIn)
    {
        window.draw(mousePoint);
    }
}

void animate::update()
{
    //cause changes to the data for the next frame
    system.Step(command);
    command = 0;
}

void animate::render()
{
    window.clear(sf::Color(245, 245, 245));
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;

    if (mouseIn)
    {
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 3,
                               sf::Mouse::getPosition(window).y - 3);

        //mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }

    while (window.pollEvent(event)) //or wait event
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();

            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::F1:
                if (menu.is_open())
                {
                    menu.set_open(false);
                }
                else
                {
                    menu.set_open(true);
                }

                break;
            case sf::Keyboard::Left:
                if (!function_mode && !menu.is_open())
                {
                    //sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                    command = LEFT_ARROW;
                }

                break;
            case sf::Keyboard::Right:
                if (!function_mode && !menu.is_open())
                {
                    //sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                    command = RIGHT_ARROW;
                }

                break;
            case sf::Keyboard::Up:
                if (!function_mode && !menu.is_open())
                {
                    //sidebar[SB_KEY_PRESSED] = "UP ARROW";
                    command = UP_ARROW;
                }

                break;
            case sf::Keyboard::Down:
                if (!function_mode && !menu.is_open())
                {
                    //sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                    command = DOWN_ARROW;
                }

                break;
            case sf::Keyboard::Escape:
                if (!menu.is_open())
                {
                    if (function_mode)
                    {
                        //sidebar[SB_KEY_PRESSED] = "ESC: EXIT";

                        function_mode = false;
                        function_input_label.setString("Function Input: Off");
                        function_input_label.setFillColor(sf::Color::Black);
                    }
                    else
                    {
                        window.close();
                    }
                }
                else
                {
                    menu.set_open(false);
                }
                window.pollEvent(event); //gets rid of key press event (otherwise text_entered event will view backspace as an inputted char)

                break;
            case sf::Keyboard::F: //F is used for enabling function mode
                if (!function_mode && !menu.is_open())
                {
                    function_mode = true;
                    window.pollEvent(event); //needed to get rid of key press event

                    function_input_label.setString("Function Input: On");
                    function_input_label.setFillColor(sf::Color::Red);
                }

                break;
            case sf::Keyboard::Enter: //enter can also be used for enabling and disabling function mode
                if (!menu.is_open())
                {
                    if (function_mode)
                    {
                        function_mode = false;

                        function_input_label.setString("Function Input: Off");
                        function_input_label.setFillColor(sf::Color::Black);
                    }
                    else
                    {
                        function_mode = true;

                        function_input_label.setString("Function Input: On");
                        function_input_label.setFillColor(sf::Color::Red);
                    }
                    window.pollEvent(event); //gets rid of key press event (otherwise text_entered event will view ENTER as an inputted char)
                }

                break;
            case sf::Keyboard::Backspace:
                if (function_mode && !_graph_info->_equation.empty())
                {
                    _graph_info->_equation.pop_back(); //removes last element of string
                }
                window.pollEvent(event); //gets rid of key press event (otherwise text_entered event will view backspace as an inputted char)
                command = NEW_FUNCTION;  //just so the function updates, probably unnecessary

                break;
            case sf::Keyboard::R:
                if (!function_mode)
                {
                    command = RESET_GRAPH;
                }

                break;
            case sf::Keyboard::S:
                if (menu.is_open())
                {
                    save(filename.c_str(), sidebar.get_items());
                }

                break;
            case sf::Keyboard::L:
                if (menu.is_open())
                {
                    load(filename.c_str(), sidebar.get_items());
                }

                break;
            }

            break;
        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            //Do something with it if you need to...
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < DOMAIN_POSITION - 1; i++)
                {
                    if (invis_rectangles[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        if (sidebar[i] != "")
                        {
                            _graph_info->_equation = sidebar[i];
                            command = NEW_FUNCTION;
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < DOMAIN_POSITION - 1; i++)
                {
                    if (invis_rectangles[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        sidebar[i] = _graph_info->_equation;
                    }
                }
            }

            break;
        case sf::Event::MouseWheelScrolled:
            if (!menu.is_open())
            {
                if (event.mouseWheelScroll.delta < 0)
                {
                    command = CMD_ZOOM_OUT;
                }
                else
                {
                    command = CMD_ZOOM_IN;
                }
            }
            window.pollEvent(event); //to avoid mouse scrolls being sent into TextEntered event

            break;
        case sf::Event::TextEntered:
            if (function_mode && !menu.is_open()) //only executes if function_mode is enabled and menu is not open
            {
                if (event.text.unicode >= 32 && event.text.unicode <= 126) //checking to see if unicode is valid char, then static casting to char
                {                                                          //think i need to adjust these values
                    _graph_info->_equation += static_cast<char>(event.text.unicode);
                    command = NEW_FUNCTION;
                }
            }

            break;
        default:
            break;
        }
    }

    //this uses stringstream to convert the domain to a string of one decimal place
    stringstream domain_x, domain_y;

    domain_x << fixed << setprecision(2) << _graph_info->_domain.x;
    string domain_x_str = domain_x.str();
    domain_y << fixed << setprecision(2) << _graph_info->_domain.y;
    string domain_y_str = domain_y.str();

    sidebar[DOMAIN_POSITION] = "Domain: [" + domain_x_str + ", " + domain_y_str + "]";

    //setting functin label each loop
    function_label.setString(_graph_info->_equation);
    function_label.setPosition(sf::Vector2f(WORK_PANEL - function_label.getLocalBounds().width - 10, function_label.getCharacterSize()));
}

void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); //clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string animate::mouse_pos_string(sf::RenderWindow &window)
{
    translate translator(_graph_info);

    //this uses stringstream to convert to a string of one decimal place
    stringstream mousepos_x, mousepos_y;

    mousepos_x << fixed << setprecision(2) << translator.reverse_translate(sf::Mouse::getPosition(window)).x;
    string mousepos_x_str = mousepos_x.str();
    mousepos_y << fixed << setprecision(2) << translator.reverse_translate(sf::Mouse::getPosition(window)).y;
    string mousepos_y_str = mousepos_y.str();

    return "(" +
           mousepos_x_str +
           ", " +
           mousepos_y_str +
           ")";
}

bool animate::save(const char fname[], const vector<string> &list)
{
    ofstream f;
    f.open(fname);

    if (f.fail())
    {
        cout << "FAILED TO LOAD EQUATIONS FILE";
        return false;
    }

    vector<string>::const_iterator sidebar_end = list.end() - 3; //so file only loads in as many lines as there are boxes on the sidebar

    for (vector<string>::const_iterator it = list.begin(); it != sidebar_end; it++)
    {
        f << *it << endl;
    }

    f.close();
    return true;
}
bool animate::load(const char fname[], vector<string> &list)
{
    ifstream f;
    f.open(fname);

    if (f.fail())
    {
        cout << "FAILED TO LOAD EQUATIONS FILE";
        sidebar[0] = "X";
        return false;
    }

    vector<string>::iterator sidebar_end = list.end() - 3; //so file only loads in as many lines as there are boxes on the sidebar

    for (vector<string>::iterator it = list.begin(); it != sidebar_end; it++)
    {
        getline(f, *it);
    }

    f.close();

    return true;
}