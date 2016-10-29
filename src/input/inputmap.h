#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <keyinput.h>
#include <buttoninput.h>
#include <joystickinput.h>
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
    std::map<std::string,JoystickInput> axes;
    std::map<std::string,KeyInput> keys;

    std::map<std::string,KeyInput>::iterator it;
    std::map<std::string,ButtonInput>::iterator bt;
    std::map<std::string,JoystickInput>::iterator jt;

public:
    InputMap();

    bool buttonPressed(std::string);
    bool buttonToggled(std::string);

    bool keyToggled(std::string);
    bool keyPressed(std::string);

    void setKeyInput(std::string,sf::Keyboard::Key);
    void setKeyInput(std::string,int);

    std::vector<std::string> getKeysDown();
    std::vector<std::string> getButtonsDown();
    std::vector<std::string> getJoystickInput();

    void setButtonInput(std::string,int);

    void update();

    Controller *getController() const;
    void setController(Controller *value);
};
}

#endif // INPUTMAP_H
