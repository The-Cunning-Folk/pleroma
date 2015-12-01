#ifndef CONTROLLER_H
#define CONTROLLER_H


#include<SFML/Graphics.hpp>
#include<map>
#include<memory>
#include<string>
#include<iostream>

namespace BQ{
class InputMap;

class Controller
{
public:
    Controller();
    Controller(unsigned int,unsigned int,std::vector<std::string>);

    unsigned int index;
    unsigned int buttons;

    std::vector<std::string> axes;
    std::vector<sf::Joystick::Axis> indices;

    bool isConnected();
    bool isBound();

    InputMap* parent;

    bool isButtonPressed(int);

    float getAxis(sf::Joystick::Axis);

    float getXAxis();
    float getYAxis();
    float getZAxis();
    float getRAxis();
    float getUAxis();
    float getVAxis();

    std::map<std::string,float> getAxes();

    InputMap *getParent() const;
    void setParent(InputMap *value);
};
}

#endif // CONTROLLER_H
