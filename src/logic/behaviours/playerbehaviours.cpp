#include "playerbehaviours.h"

#include <gameobject.h>

using namespace BQ;

PlayerBehaviours::PlayerBehaviours()
{

}

void PlayerBehaviours::resolveEvents()
{
    float speed = delta*200.0;
    for(unsigned int i=0; i<events.size(); i++)
    {

        Event event = events[i];
        Transform & transform = event.triggeredBy->loadTransform();

        if(event.parsedScript["action"].compare("move_right")==0)
        {
            transform.move(speed,0.0);
        }
        if(event.parsedScript["action"].compare("move_up")==0)
        {
            transform.move(0.0,-speed);
        }
        if(event.parsedScript["action"].compare("move_left")==0)
        {
            transform.move(-speed,0.0);
        }
        if(event.parsedScript["action"].compare("move_down")==0)
        {
            transform.move(0.0,speed);
        }
        if(event.parsedScript["action"].compare("X")==0)
        {
            float deltaX = std::stof(event.parsedScript["val"])*0.01;
            transform.move(speed*deltaX,0.0);
        }
        if(event.parsedScript["action"].compare("Y")==0)
        {
            float deltaY = std::stof(event.parsedScript["val"])*0.01;
            transform.move(0.0,speed*deltaY);
        }
    }
}

