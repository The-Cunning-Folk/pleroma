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
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

    }
};
}

#endif // PLAYERINPUT_H
