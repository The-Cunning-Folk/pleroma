#ifndef PLAYERBEHAVIOURS_H
#define PLAYERBEHAVIOURS_H

#include<behaviour.h>

namespace BQ{
class PlayerBehaviours : public Behaviour
{
public:
    PlayerBehaviours();

    float dx;
    float dy;
    float speed;
    float baseSpeed;
    std::string facing;

    std::string getFacing(float,float);

    void resolveEvents();
    void update();
};
}

#endif // PLAYERBEHAVIOURS_H
