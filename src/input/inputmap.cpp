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
    newInput.name = name;
    keys[name] = newInput;
}

std::vector<std::string> InputMap::getKeysDown()
{
    std::vector<std::string>keysDown(0);
    for(it = keys.begin(); it != keys.end(); it++) {
        KeyInput& input = it->second;
        if(input.isDown)
        {
            keysDown.push_back(input.name);
        }
    }
    return(keysDown);
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

