#include "gamewindow.h"

GameWindow::GameWindow()
{
   window.create(sf::VideoMode(480, 270), "Default Window");
}

GameWindow::GameWindow(int width, int height, std::string name)
{
   window.create(sf::VideoMode(width, height), name);
}

void GameWindow::run()
{
    while (window.isOpen())
    {
        //window management
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       //end window management

        window.clear();

        //drawing goes here

        //end drawing

        window.display();
    }
}
