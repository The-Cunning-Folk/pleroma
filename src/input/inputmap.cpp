#include "inputmap.h"

using namespace BQ;

Controller *InputMap::getController() const
{
    return controller;
}

void InputMap::setController(Controller *value)
{
    value->setParent(this);
    controller = value;

    //todo: load this from file!
    std::vector<std::string> mapping(0);
    mapping.push_back("pad_A");
    mapping.push_back("pad_B");
    mapping.push_back("pad_X");
    mapping.push_back("pad_Y");
    mapping.push_back("LB");
    mapping.push_back("RB");
    mapping.push_back("back");
    mapping.push_back("start");
    mapping.push_back("LS");
    mapping.push_back("RS");

    for(unsigned int i=0; i<controller->buttons; i++){
        if(i>mapping.size()-1){
            break;
        }
        ButtonInput btn(mapping[i],i);
        buttons[mapping[i]] = btn;
    }

    for(unsigned int i=0; i<controller->axes.size(); i++) {
        JoystickInput jstk(controller->axes[i],controller->indices[i]);
        axes[controller->axes[i]] = jstk;
    }
}

InputMap::InputMap()
{

}

bool InputMap::buttonPressed(std::string name)
{
    if(!buttons.count(name))
    {
        return false;
    }
    return(buttons[name].isDown);
}

bool InputMap::buttonToggled(std::string name)
{
    if(!buttons.count(name))
    {
        return false;
    }
    return(buttons[name].toggled);
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

std::vector<std::string> InputMap::getButtonsDown()
{
    std::vector<std::string>buttonsDown(0);
    for(bt = buttons.begin(); bt != buttons.end(); bt++) {
        ButtonInput& button = bt->second;
        if(button.isDown){
            buttonsDown.push_back(button.name);
        }
    }
    return buttonsDown;
}

std::vector<std::string> InputMap::getJoystickInput()
{
    std::vector<std::string>joystickInputs(0);
    for(jt = axes.begin(); jt != axes.end(); jt++) {
        JoystickInput& axis = jt->second;
        if(fabs(axis.getPosition()) > 0.0)
        {
            std::string joystr = axis.name + "(" + std::to_string(axis.getPosition()) + ")";
            joystickInputs.push_back(joystr);
        }
    }
    return joystickInputs;
}


void InputMap::setButtonInput(std::string, int)
{

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

    if(controller != NULL){
        for(bt = buttons.begin(); bt != buttons.end(); bt++) {
            ButtonInput& button = bt->second;
            if(controller->isButtonPressed(button.buttonIndex))
            {
                button.isDown = true;
            }
            else
            {
                if(button.isDown)
                {
                    button.toggled = true;
                }
                else
                {
                    button.toggled = false;
                }
                button.isDown = false;
            }
        }

        for(jt = axes.begin(); jt != axes.end(); jt++) {
            JoystickInput& axis = jt->second;
            axis.position = controller->getAxis(axis.axis);
        }

    }
}

