#ifndef PLAYERBEHAVIOURS_H
#define PLAYERBEHAVIOURS_H

#include<behaviour.h>
#include <convexpolygon.h>

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

    sf::Time rollTimer;
    sf::Clock rollClock;
    sf::Time attackTimer;
    sf::Clock attackClock;

    sf::Vector2f rollDirection;
    sf::Vector2f attackDirection;
    sf::Vector2f direction;


    bool startRoll;
    bool rolling;
    bool rollCooled;
    float rollDuration;
    float rollCooldown;
    float rollBoost;

    bool startAttack;
    bool attacking;
    bool attackCooled;
    float attackDuration;
    float attackCooldown;
    float attackMom;
    float attackScaleFactor;

    float attackFrameLength;
    int attackFrame;
    std::vector <ConvexPolygon> attackFrames;

    std::string getFacing(float,float);
    sf::Vector2f getOctDirection();
    void checkInputLogic();

    void collisionWith(GameObject &, std::string, std::string);

    void beforeEvents();
    void resolveEvent(Event &);
    void update();
};
}

#endif // PLAYERBEHAVIOURS_H
