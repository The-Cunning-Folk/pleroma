#include "inputfactory.h"

using namespace BQ;

InputFactory::InputFactory()
{

}

InputEngine *InputFactory::getInputEngine() const
{
    return inputEngine;
}

void InputFactory::setInputEngine(InputEngine *value)
{
    inputEngine = value;
}

void InputFactory::detectControllers()
{
    for(int i = 0; i<8; i++)
    {
        bool connected = sf::Joystick::isConnected(i);
        if(connected)
        {
            debug->printinfo("joystick: " + std::to_string(i));
            unsigned int buttons = sf::Joystick::getButtonCount(i);
            debug->printinfo("buttons: " + std::to_string(buttons));
            bool hasX = sf::Joystick::hasAxis(i, sf::Joystick::X);
            bool hasY = sf::Joystick::hasAxis(i, sf::Joystick::Y);
            bool hasZ = sf::Joystick::hasAxis(i, sf::Joystick::Z);
            bool hasR = sf::Joystick::hasAxis(i, sf::Joystick::R);
            bool hasU = sf::Joystick::hasAxis(i, sf::Joystick::U);
            bool hasV = sf::Joystick::hasAxis(i, sf::Joystick::V);

            debug->printinfo("has X: " + std::to_string(hasX));
            debug->printinfo("has Y: " + std::to_string(hasY));
            debug->printinfo("has Z: " + std::to_string(hasZ));
            debug->printinfo("has R: " + std::to_string(hasR));
            debug->printinfo("has U: " + std::to_string(hasU));
            debug->printinfo("has V: " + std::to_string(hasV));

            std::vector<std::string> axes;

            if(hasX){axes.push_back("X");}
            if(hasY){axes.push_back("Y");}
            if(hasZ){axes.push_back("Z");}
            if(hasR){axes.push_back("R");}
            if(hasU){axes.push_back("U");}
            if(hasV){axes.push_back("V");}

            std::string axesList = "";

            for(int j=0; j<axes.size(); j++)
            {
                axesList += axes[j];
                if(j!=axes.size()-1)
                {
                    axesList += ", ";
                }
            }

            debug->printinfo("found a controller with " + std::to_string(buttons)
                             + " buttons, and " + axesList + " axes");

            Controller ctrl;
            ctrl.index = i;
            ctrl.buttons = buttons;
            ctrl.axes = axes;

            inputEngine->addController(ctrl);
        }
    }
}

