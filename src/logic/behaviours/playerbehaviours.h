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

    bool startRoll;
    bool rolling;
    bool rollCooled;
    sf::Time rollTimer;
    sf::Clock rollClock;
    sf::Vector2f rollDirection;
    float rollDuration;
    float rollCooldown;
    float rollBoost;

    std::string getFacing(float,float);

    void resolveEvents();
    void update();
};
}

#endif // PLAYERBEHAVIOURS_H
