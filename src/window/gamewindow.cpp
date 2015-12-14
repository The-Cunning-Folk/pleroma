#include "gamewindow.h"

using namespace BQ;

GameWindow::GameWindow()
{
   window.create(sf::VideoMode(480, 270), "Default Window");
   window.setFramerateLimit(120);
}

GameWindow::GameWindow(int width, int height, std::string name)
{
   window.create(sf::VideoMode(width, height), name);
   this->width = width;
   this->height = height;
}

GameWindow::GameWindow(GameWindow & gameWindow)
{
    GameWindow(gameWindow.getWidth(),gameWindow.getHeight(),gameWindow.getName());
}

bool GameWindow::isOpen()
{
   return window.isOpen();
}

void GameWindow::clear()
{
    window.clear();
}

void GameWindow::display()
{
    window.display();
}

void GameWindow::close()
{
    window.close();
}

void GameWindow::setTag(std::string newtag)
{
    tag = newtag;
}

void GameWindow::setName(std::string newname)
{
    name = newname;
}

void GameWindow::setWidth(int newwidth)
{
    width = newwidth;
}

void GameWindow::setHeight(int newheight)
{
    height = newheight;
}

int GameWindow::getHeight()
{
    return height;
}

int GameWindow::getWidth()
{
    return width;
}

std::string GameWindow::getName()
{
    return name;
}

void GameWindow::updateEvents()
{

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::Resized){
            width = window.getSize().x;
            height = window.getSize().y;
        }
    }

}

void GameWindow::draw(const sf::Drawable & tex)
{
    window.draw(tex);
}

void GameWindow::draw()
{

}
