#include "eventfactory.h"


using namespace BQ;
EventFactory::EventFactory()
{

}

void EventFactory::createEvent(std::string script, GameObject * object)
{
    Event event;
    event.script = script;
    event.triggeredBy = object;
    eventEngine->pushEvent(event);
}

void EventFactory::createCollision(Collision c)
{
    eventEngine->collisions.push_back(c);
}

EventEngine *EventFactory::getEventEngine() const
{
    return eventEngine;
}

void EventFactory::setEventEngine(EventEngine *value)
{
    eventEngine = value;
}

