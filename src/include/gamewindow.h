#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>


class GameWindow
{
public:
    GameWindow();
    GameWindow(int,int,std::string);

    void run();

private:

    int width,height;
    sf::RenderWindow window;

};

#endif // GAMEWINDOW_H
