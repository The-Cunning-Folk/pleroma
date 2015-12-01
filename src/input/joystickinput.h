#ifndef JOYSTICKINPUT_H
#define JOYSTICKINPUT_H

#include<basicinput.h>
#include<SFML/Graphics.hpp>
#include<iostream>

namespace BQ{
class JoystickInput : public BasicInput
{
public:
    JoystickInput();
    JoystickInput(std::string,sf::Joystick::Axis);

    sf::Joystick::Axis axis;

    float tolerance;
    float position;

    float getPosition() const;
};
}

#endif // JOYSTICKINPUT_H
