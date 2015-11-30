#include "eventengine.h"

#include<eventfactory.h>

using namespace BQ;

EventEngine::EventEngine()
{

}

void EventEngine::run()
{
    for(int i=0; i<events.size();i++)
    {
        resolve(events[i]);
    }
    events.clear();
}

void EventEngine::pushEvent(Event event)
{
    events.push_back(event);

}

void EventEngine::resolveGlobally(std::string script)
{

}

void EventEngine::resolveLocally(Event& event)
{
    //just temporary code until I can get this working, should be handled with polymorphic behaviour components
    float speed = delta*200.0;
    if(event.script.compare("move_right")==0)
    {
        event.triggeredBy->getTransform()->move(speed,0.0);
    }
    if(event.script.compare("move_up")==0)
    {
        event.triggeredBy->getTransform()->move(0.0,-speed);
    }
    if(event.script.compare("move_left")==0)
    {
        event.triggeredBy->getTransform()->move(-speed,0.0);
    }
    if(event.script.compare("move_down")==0)
    {
        event.triggeredBy->getTransform()->move(0.0,speed);
    }
}

void EventEngine::resolve(Event& event)
{
    resolveGlobally(event.script);
    resolveLocally(event);
}

float EventEngine::getDelta() const
{
    return delta;
}

void EventEngine::setDelta(float value)
{
    delta = value;
}

