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

        if(event.script.compare("key_input[move_right]")==0)
        {
            event.triggeredBy->getTransform()->move(speed,0.0);
        }
        if(event.script.compare("key_input[move_up]")==0)
        {
            event.triggeredBy->getTransform()->move(0.0,-speed);
        }
        if(event.script.compare("key_input[move_left]")==0)
        {
            event.triggeredBy->getTransform()->move(-speed,0.0);
        }
        if(event.script.compare("key_input[move_down]")==0)
        {
            event.triggeredBy->getTransform()->move(0.0,speed);
        }
    }
}

