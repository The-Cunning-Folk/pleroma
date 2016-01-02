#include "playerinput.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;

PlayerInput::PlayerInput()
{
    typeId = "input";
}

void PlayerInput::update()
{
    inputMap.update();
}
