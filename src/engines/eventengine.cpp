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
        debug->println(events[i].script);
    }
    events.clear();
}

void EventEngine::pushEvent(Event event)
{
    events.push_back(event);

}

float EventEngine::getDelta() const
{
    return delta;
}

void EventEngine::setDelta(float value)
{
    delta = value;
}

