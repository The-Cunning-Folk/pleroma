#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include <component.h>
#include <inputmap.h>

namespace BQ{
class PlayerInput : public Component
{
public:
    PlayerInput();

    InputMap inputMap;

    void update();

private:

};
}

#endif // PLAYERINPUT_H
