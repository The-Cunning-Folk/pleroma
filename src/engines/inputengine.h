#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include <engine.h>
#include <playerinput.h>

namespace BQ{
class InputEngine : public Engine
{
public:
    InputEngine();

    void run();

    std::vector<Controller> controllers;

    std::vector<PlayerInput> inputs;

    PlayerInput& addPlayerInput();

    Controller* addController(Controller);

};
}

#endif // INPUTENGINE_H
