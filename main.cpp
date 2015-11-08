#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 270), "SFML works!");

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

    return 0;
}
