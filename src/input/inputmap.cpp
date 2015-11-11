#include "inputmap.h"

using namespace BQ;

InputMap::InputMap()
{

}

bool InputMap::keyToggled(std::string name)
{
    if(!keys.count(name))
    {
        return false;
    }
    return(keys[name].toggled);
}

bool InputMap::keyPressed(std::string name)
{
    if(!keys.count(name))
    {
        return false;
    }
    return(keys[name].isDown);
}

void InputMap::setKeyInput(std::string name, sf::Keyboard::Key key)
{
    KeyInput newInput(key);
    keys[name] = newInput;
}

void InputMap::update()
{

    for(it = keys.begin(); it != keys.end(); it++) {
        KeyInput& input = it->second;
        if(sf::Keyboard::isKeyPressed(input.key))
        {
            input.isDown = true;
        }
        else
        {
            if(input.isDown)
            {
                input.toggled = true;
            }
            else
            {
                input.toggled = false;
            }
            input.isDown = false;
        }
    }
}

