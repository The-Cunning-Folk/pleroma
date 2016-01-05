#include "playerbehaviours.h"

#include <gameobject.h>
#include<componentloader.h>
#include<gameobjectloader.h>

using namespace BQ;

PlayerBehaviours::PlayerBehaviours()
{
    baseSpeed = 200.0;
    facing = "d";
    startRoll = false;
    rolling = false;
    rollCooled = true;
    rollDuration = 0.25;
    rollCooldown = 0.5;
    rollBoost = 2.5;

    attackDuration = 0.25;
    attackCooldown = 0.05;
    startAttack = false;
    attackCooled = false;
    attacking = false;
}

std::string PlayerBehaviours::getFacing(float dx, float dy)
{
    direction.x = dx;
    direction.y = dy;
    if(direction.x == 0) {
        if(direction.y < 0){
            facing = "u";
        }
        else if (direction.y > 0)
        {
            facing = "d";
        }
    }
    else
    {
        float dirRatio = direction.y/direction.x;
        float absRatio = fabs(dirRatio);

        if(absRatio <= 0.41)
        {
            if(direction.x > 0)
            {
                facing = "r";
            }
            else
            {
                facing = "l";
            }
        }
        else if(absRatio > 0.41 && absRatio <= 2.41)
        {
            facing = "";

            if(direction.y > 0)
            {
                facing += "d";
            }
            else
            {
                facing += "u";
            }

            if(direction.x > 0)
            {
                facing += "r";
            }
            else
            {
                facing += "l";
            }
        }
    }
    return facing;
}

sf::Vector2f PlayerBehaviours::getOctDirection()
{
    sf::Vector2f octDir;
    if(compare(facing,"l"))
    {
        octDir = sf::Vector2f(-1,0);
    }
    else if(compare(facing,"ul"))
    {
        octDir = sf::Vector2f(-1,-1);
    }
    else if(compare(facing,"u"))
    {
        octDir = sf::Vector2f(0,-1);
    }
    else if(compare(facing,"ur"))
    {
        octDir = sf::Vector2f(1,-1);
    }
    else if(compare(facing,"r"))
    {
        octDir = sf::Vector2f(1,0);
    }
    else if(compare(facing,"dr"))
    {
        octDir = sf::Vector2f(1,1);
    }
    else if(compare(facing,"d"))
    {
        octDir = sf::Vector2f(0,1);
    }
    else if(compare(facing,"dl"))
    {
        octDir = sf::Vector2f(-1,1);
    }
    octDir = maths->unit(octDir);
    return octDir;
}

void PlayerBehaviours::checkInputLogic()
{
    if(startRoll && !attacking)
    {
        rolling = true;
        startRoll = false;
        rollDirection = direction;
    }
    if(rolling)
    {

        if(rollTimer.asSeconds() >= rollDuration)
        {
            rolling = false;
        }
    }
    if(!rolling && !rollCooled)
    {
        if(rollTimer.asSeconds() > rollDuration + rollCooldown)
        {
            rollCooled = true;
        }
    }

    if(startAttack && !rolling)
    {
        attacking = true;
        startAttack = false;
        attackDirection = getOctDirection();
    }
    if(attacking)
    {
        if(attackTimer.asSeconds() >= attackDuration)
        {
            attacking = false;
        }
    }
    if(!attacking && !attackCooled)
    {
        if(attackTimer.asSeconds() > attackDuration + attackCooldown)
        {
            attackCooled = true;
        }
    }
}

void PlayerBehaviours::resolveEvents()
{
    speed = delta*baseSpeed;
    dx = 0;
    dy = 0;

    for(unsigned int i=0; i<events.size(); i++)
    {

        Event & event = events[i];


        std::string action = event.parsedScript["action"];

        if(compare(action,"move_right"))
        {
            dx += 1;
        }
        else if(compare(action,"move_up"))
        {
            dy -= 1;
        }
        else if(compare(action,"move_left"))
        {
            dx -= 1;
        }
        else if(compare(action,"move_down"))
        {
            dy += 1;
        }
        else if(compare(action,"attack") || compare(action,"pad_X"))
        {
            if(attackCooled)
            {
                startAttack = true;
                attackCooled = false;
                attackClock.restart();
            }
        }
        else if(compare(action,"roll") || compare(action,"pad_A"))
        {
            if(rollCooled)
            {
                startRoll = true;
                rollCooled = false;
                rollClock.restart();
            }
        }
        else if(compare(action,"X"))
        {
            float deltaX = std::stof(event.parsedScript["val"])*0.01;
            dx += deltaX;
        }
        else if(compare(action,"Y"))
        {
            float deltaY = std::stof(event.parsedScript["val"])*0.01;
            dy += deltaY;
        }
    }
}

void PlayerBehaviours::update()
{
    Transform & transform = gameObjectLoader->loadGameObject(parent).loadTransform();
    sf::Vector2f direction(dx,dy);
    if(maths->mag(direction) > 1.0)
    {
        direction = maths->unit(direction);
    }
    sf::Vector2f velocity = speed*direction;
    facing = getFacing(direction.x,direction.y);
    rollTimer = rollClock.getElapsedTime();    
    attackTimer = attackClock.getElapsedTime();

    checkInputLogic();

    if(rolling)
    {
        velocity = rollBoost*speed*rollDirection;
    }
    if(attacking)
    {
        velocity.x = 0;
        velocity.y = 0;
        Collidable & attack = componentLoader->getCollidableFromObject(gameObjectLoader->loadGameObject(parent),"attack");
        attack.polygon.clearPoints();
        sf::Vector2f p1 = (maths->rotateAntiClockwise(attackDirection,0.7));
        sf::Vector2f p2 = (maths->rotateClockwise(attackDirection,0.7));
        p1 = 30.0F*p1;
        p2 = 30.0F*p2;
        attack.polygon.addPoint(sf::Vector2f(0,0));
        attack.polygon.addPoint(p1);
        attack.polygon.addPoint(p2);
    }
    else
    {
        Collidable & attack = componentLoader->getCollidableFromObject(gameObjectLoader->loadGameObject(parent),"attack");
        attack.polygon.clearPoints();
    }

    transform.move(velocity);
}

