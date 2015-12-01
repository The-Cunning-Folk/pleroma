#include "joystickinput.h"

using namespace BQ;

JoystickInput::JoystickInput()
{
    tolerance = 15.0;
}

JoystickInput::JoystickInput(std::string name, sf::Joystick::Axis axis)
{
    this->name = name;
    this->axis = axis;
    tolerance = 15.0;
}

float JoystickInput::getPosition() const
{

    if(abs(position)<tolerance){
        return 0.0;
    }
    return position;
}

