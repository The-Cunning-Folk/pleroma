#include "inputengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<gameobjectloader.h>
#include<game.h>


using namespace BQ;

InputEngine::InputEngine() : Engine()
{
    placeholder = "auto_input_";
}

void InputEngine::wake()
{

}

void InputEngine::start()
{

}

void InputEngine::run()
{
    //check for inputs

    for(unsigned int i = 0; i<controllers.size(); i++)
    {

    }

    EventFactory& eFactory = game->eventFactory;

    GameObjectStore & os = game->getCurrentLevel().objects;

    for(it_playerinput it = os.playerInputs.begin(); it != os.playerInputs.end(); it++)
    {
        PlayerInput & p = it->second;
        p.update();
        std::vector<std::string> activeInputs = p.inputMap.getKeysDown();
        std::vector<std::string> activeButtons = p.inputMap.getButtonsDown();
        std::vector<std::string> activeAxes = p.inputMap.getJoystickInput();
        if(activeInputs.size() > 0){
            for(unsigned int j = 0; j<activeInputs.size();j++)
            {
                eFactory.createEvent("key_input{" + activeInputs[j] + "}",p.getParent());
            }
        }
        if(activeButtons.size() > 0){
            for(unsigned int j = 0; j<activeButtons.size();j++)
            {
                eFactory.createEvent("button_input{" + activeButtons[j] + "}",p.getParent());
            }
        }
        if(activeAxes.size() > 0){
            for(unsigned int j = 0; j<activeAxes.size(); j++)
            {
                eFactory.createEvent("joystick_input{" +activeAxes[j] + "}",p.getParent());
            }
        }
    }

    for(unsigned int i = 0; i<controllers.size(); i++)
    {

    }
}

void InputEngine::finish()
{

}


Controller *InputEngine::addController(Controller ctrl)
{
    controllers.push_back(ctrl);
    return &controllers.back();
}

