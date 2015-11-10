#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>

namespace BQ{
    class GameWindow
    {
    public:
        GameWindow();
        GameWindow(int,int,std::string);
        GameWindow(GameWindow&);

        void updateEvents();

        //expanded sfml renderwindow functionality

        bool isOpen();
        void clear();
        void display();
        void close();
        void draw(const sf::Drawable&);
        void draw();

        //getters and setters

        void setTag(std::string);
        void setName(std::string);
        void setWidth(int);
        void setHeight(int);

        int getHeight();
        int getWidth();
        std::string getName();

        sf::RenderWindow window;

    private:

        int width,height;
        std::string name;
        std::string tag;

    };
}

#endif // GAMEWINDOW_H
