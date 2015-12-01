#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <keyinput.h>
#include <buttoninput.h>
#include <controller.h>
#include <map>
#include <memory>
#include <string>
#include<iostream>

namespace BQ {
class InputMap
{

private:

    Controller* controller;

    std::map<std::string,ButtonInput> buttons;
    std::map<std::string,float> axes;
    std::map<std::string,KeyInput> keys;
    std::map<std::string,KeyInput>::iterator it;
    std::map<std::string,ButtonInput>::iterator bt;

public:
    InputMap();

    bool buttonPressed(std::string);
    bool buttonToggled(std::string);

    bool keyToggled(std::string);
    bool keyPressed(std::string);

    void setKeyInput(std::string,sf::Keyboard::Key);

    std::vector<std::string> getKeysDown();
    std::vector<std::string> getButtonsDown();

    void setButtonInput(std::string,int);

    void update();

    Controller *getController() const;
    void setController(Controller *value);
};
}

#endif // INPUTMAP_H
