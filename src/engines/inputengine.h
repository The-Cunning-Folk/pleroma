#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include <engine.h>
#include <playerinput.h>

namespace BQ{
class InputEngine : public Engine
{
public:
    InputEngine();

    void wake();

    void start();
    void run();
    void finish();

    std::vector<Controller> controllers;

    Controller* addController(Controller);

};
}

#endif // INPUTENGINE_H
