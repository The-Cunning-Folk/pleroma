#include "playerinput.h"

using namespace BQ;

PlayerInput::PlayerInput()
{
    typeId = "input";
}

void PlayerInput::update()
{
    inputMap.update();
}
