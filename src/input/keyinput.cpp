#include "keyinput.h"

KeyInput::KeyInput()
{
    isDown = false;
    toggled = false;
}

KeyInput::KeyInput(sf::Keyboard::Key value)
{
    key = value;
    isDown = false;
    toggled = false;
}
