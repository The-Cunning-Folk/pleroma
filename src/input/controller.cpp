#include "controller.h"

#include<inputmap.h>

using namespace BQ;

Controller::Controller()
{
    parent = NULL;
}

Controller::Controller(unsigned int index, unsigned int buttons, std::vector<std::string> axes)
{
    this->index = index;
    this->buttons = buttons;
    this->axes = axes;
    parent = NULL;
}

bool Controller::isConnected()
{
    return sf::Joystick::isConnected(index);
}

bool Controller::isBound()
{
    return parent != NULL;
}

InputMap *Controller::getParent() const
{
    return parent;
}

void Controller::setParent(InputMap *value)
{
    parent = value;
}

bool Controller::isButtonPressed(int button)
{
    if(button > buttons - 1 || button < 0){
        return false;
    }
    return sf::Joystick::isButtonPressed(index,button);
}

float Controller::getXAxis()
{
    return sf::Joystick::getAxisPosition(index,sf::Joystick::X);
}

float Controller::getYAxis()
{
    return sf::Joystick::getAxisPosition(index,sf::Joystick::Y);
}

float Controller::getZAxis()
{
    return sf::Joystick::getAxisPosition(index,sf::Joystick::Z);
}

float Controller::getRAxis()
{
    return sf::Joystick::getAxisPosition(index,sf::Joystick::R);
}

float Controller::getUAxis()
{
    return sf::Joystick::getAxisPosition(index,sf::Joystick::U);
}

float Controller::getVAxis()
{
    return sf::Joystick::getAxisPosition(index,sf::Joystick::V);
}

std::map<std::string, float> Controller::getAxes()
{
    std::map<std::string,float> axisStates;
    axisStates["X"] = getXAxis();
    axisStates["Y"] = getYAxis();
    axisStates["Z"] = getZAxis();
    axisStates["R"] = getRAxis();
    axisStates["U"] = getUAxis();
    axisStates["V"] = getVAxis();
    return axisStates;
}

