#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <keyinput.h>
#include <map>
#include <memory>
#include <string>
#include<iostream>

namespace BQ {
class InputMap
{

private:

    std::map<std::string,KeyInput> keys;
    std::map<std::string,KeyInput>::iterator it;

public:
    InputMap();

    bool keyToggled(std::string);
    bool keyPressed(std::string);

    void setKeyInput(std::string,sf::Keyboard::Key);
    void update();

};
}

#endif // INPUTMAP_H
