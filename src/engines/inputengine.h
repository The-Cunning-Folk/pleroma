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

    std::vector<PlayerInput> inputs;

    PlayerInput* addPlayerInput();

};
}

#endif // INPUTENGINE_H
