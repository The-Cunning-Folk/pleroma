#include "inputengine.h"

using namespace BQ;

InputEngine::InputEngine()
{

}

void InputEngine::run()
{
    //check for inputs

    for(unsigned int i = 0; i<inputs.size(); i++)
    {
        inputs[i].update();
        std::vector<std::string> activeInputs = inputs[i].inputMap.getKeysDown();
        if(activeInputs.size() > 0){
            for(unsigned int j = 0; j<activeInputs.size();j++)
            {

            }
        }
    }
}

PlayerInput *InputEngine::addPlayerInput()
{
    inputs.resize(inputs.size() + 1);
    if(debug != NULL){
        inputs.back().setDebug(debug);
    }
    inputs.back().index = inputs.size();
    return(&inputs.back());
}

