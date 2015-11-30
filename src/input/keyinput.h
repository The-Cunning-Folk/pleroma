#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <SFML/Graphics.hpp>
#include<basicinput.h>

class KeyInput: public BasicInput
{
public:
    KeyInput();
    KeyInput(sf::Keyboard::Key);

    sf::Keyboard::Key key;

    bool isDown;
    bool toggled;

};

#endif // KEYINPUT_H
