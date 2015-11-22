#include "inputengine.h"

using namespace BQ;

InputEngine::InputEngine()
{

}

void InputEngine::run()
{
    //check for inputs
}

PlayerInput *InputEngine::addPlayerInput()
{
    inputs.resize(inputs.size() + 1);
    if(debug != NULL){
        inputs.back().setDebug(debug);
    }
    return(&inputs.back());
}

