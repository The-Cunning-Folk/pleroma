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

void InputMap::setKeyInput(std::string name, std::string key)
{
    setKeyInput(name,getKeyCode(key));
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

sf::Keyboard::Key InputMap::getKeyCode(std::string key)
{
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    if(key=="a"){return sf::Keyboard::A;}
    else if (key=="b"){return sf::Keyboard::B;}
    else if (key=="c"){return sf::Keyboard::C;}
    else if (key=="d"){return sf::Keyboard::D;}
    else if (key=="e"){return sf::Keyboard::E;}
    else if (key=="f"){return sf::Keyboard::F;}
    else if (key=="g"){return sf::Keyboard::G;}
    else if (key=="h"){return sf::Keyboard::H;}
    else if (key=="i"){return sf::Keyboard::I;}
    else if (key=="j"){return sf::Keyboard::J;}
    else if (key=="k"){return sf::Keyboard::K;}
    else if (key=="l"){return sf::Keyboard::L;}
    else if (key=="m"){return sf::Keyboard::M;}
    else if (key=="n"){return sf::Keyboard::N;}
    else if (key=="o"){return sf::Keyboard::O;}
    else if (key=="p"){return sf::Keyboard::P;}
    else if (key=="q"){return sf::Keyboard::Q;}
    else if (key=="r"){return sf::Keyboard::R;}
    else if (key=="s"){return sf::Keyboard::S;}
    else if (key=="t"){return sf::Keyboard::T;}
    else if (key=="u"){return sf::Keyboard::U;}
    else if (key=="v"){return sf::Keyboard::V;}
    else if (key=="w"){return sf::Keyboard::W;}
    else if (key=="x"){return sf::Keyboard::X;}
    else if (key=="y"){return sf::Keyboard::Y;}
    else if (key=="z"){return sf::Keyboard::Z;}
    else if (key=="enter" || key=="return"){return sf::Keyboard::Return;}
    else if (key=="space" || key==" "){return sf::Keyboard::Space;}
    else if (key=="0"){return sf::Keyboard::Num0;}
    else if (key=="1"){return sf::Keyboard::Num1;}
    else if (key=="2"){return sf::Keyboard::Num2;}
    else if (key=="3"){return sf::Keyboard::Num3;}
    else if (key=="4"){return sf::Keyboard::Num4;}
    else if (key=="5"){return sf::Keyboard::Num5;}
    else if (key=="6"){return sf::Keyboard::Num6;}
    else if (key=="7"){return sf::Keyboard::Num7;}
    else if (key=="8"){return sf::Keyboard::Num8;}
    else if (key=="9"){return sf::Keyboard::Num9;}
    else if (key=="."){return sf::Keyboard::Period;}
    else if (key==","){return sf::Keyboard::Comma;}
    else if (key=="/"){return sf::Keyboard::Slash;}
    return sf::Keyboard::Unknown;
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

