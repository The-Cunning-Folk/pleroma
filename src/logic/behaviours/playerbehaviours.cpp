#include "playerbehaviours.h"

#include <gameobject.h>
#include<componentloader.h>
#include<gameobjectloader.h>

using namespace BQ;

PlayerBehaviours::PlayerBehaviours()
{

}

void PlayerBehaviours::resolveEvents()
{
    speed = delta*200.0;
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
        else if(compare(action,"attack"))
        {
            std::cout << "attack" << std::endl;
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
    transform.move(velocity);
}

