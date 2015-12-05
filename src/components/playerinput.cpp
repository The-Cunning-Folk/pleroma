#include "playerinput.h"
#include <componentloader.h>

using namespace BQ;

PlayerInput::PlayerInput()
{
    typeId = "input";
}

void PlayerInput::update()
{
    inputMap.update();
}
