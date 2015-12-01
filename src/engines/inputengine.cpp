#include "inputengine.h"

#include<eventfactory.h>

using namespace BQ;

InputEngine::InputEngine()
{

}

void InputEngine::run()
{
    //check for inputs

    for(unsigned int i = 0; i<controllers.size(); i++)
    {

    }

    for(unsigned int i = 0; i<inputs.size(); i++)
    {
        inputs[i].update();
        std::vector<std::string> activeInputs = inputs[i].inputMap.getKeysDown();
        std::vector<std::string> activeButtons = inputs[i].inputMap.getButtonsDown();
        std::vector<std::string> activeAxes = inputs[i].inputMap.getJoystickInput();
        if(activeInputs.size() > 0){
            for(unsigned int j = 0; j<activeInputs.size();j++)
            {
                eventFactory->createEvent("key_input[" + activeInputs[j] + "]",inputs[i].getParent());
            }
        }
        if(activeButtons.size() > 0){
            for(unsigned int j = 0; j<activeButtons.size();j++)
            {
                eventFactory->createEvent("button_input[" + activeButtons[j] + "]",inputs[i].getParent());
            }
        }
        if(activeAxes.size() > 0){
            for(unsigned int j = 0; j<activeAxes.size(); j++)
            {
                eventFactory->createEvent("joystick_input[" +activeAxes[j] + "]",inputs[i].getParent());
            }
        }
    }

    for(unsigned int i = 0; i<controllers.size(); i++)
    {
//        debug->printVal("X AXIS: ",controllers[i].getXAxis());
//        debug->printVal("Y AXIS: ",controllers[i].getXAxis());
//        debug->printVal("Z AXIS: ",controllers[i].getXAxis());
//        debug->printVal("R AXIS: ",controllers[i].getXAxis());
//        debug->printVal("U AXIS: ",controllers[i].getXAxis());
//        debug->printVal("V AXIS: ",controllers[i].getXAxis());

//        for(unsigned int j = 0; j<controllers[i].buttons; j++)
//        {
//            if(controllers[i].isButtonPressed(j))
//            {
//                debug->println("button: " + std::to_string(j));
//            }
//        }
    }
}


PlayerInput *InputEngine::addPlayerInput()
{
    inputs.resize(inputs.size() + 1);
    if(debug != NULL){
        inputs.back().setDebug(debug);
    }
    inputs.back().index = inputs.size();
    debug->println(std::to_string(controllers.size()));
    if(controllers.size() > 0){
        for(unsigned int i = 0; i<controllers.size(); i++)
        {
            debug->println(std::to_string(controllers[i].isBound()));
            if(!controllers[i].isBound())
            {
                debug->println("adding controller!");
                inputs.back().inputMap.setController(&controllers[i]);
            }
        }
    }
    return(&inputs.back());
}

Controller *InputEngine::addController(Controller ctrl)
{
    controllers.push_back(ctrl);
    return &controllers.back();
}

