#include "eventfactory.h"

#include <game.h>


using namespace BQ;
EventFactory::EventFactory()
{

}

Game *EventFactory::getGame() const
{
    return game;
}

void EventFactory::setGame(Game *value)
{
    game = value;
}

void EventFactory::createEvent(std::string script, std::string name)
{
    Event event;
    event.script = script;
    event.triggeredBy = name;
    eventEngine->pushEvent(event);
}

void EventFactory::createEvent(std::string script, GameObject & object)
{
    createEvent(script,object.name);
}

void EventFactory::createCollision(Collision c)
{
    eventEngine->collisions.push_back(c);
}

void EventFactory::createPhysicsExchange(PhysicalExchange p)
{
    game->physicsEngine.addCollision(p);
}

EventEngine *EventFactory::getEventEngine() const
{
    return eventEngine;
}

void EventFactory::setEventEngine(EventEngine *value)
{
    eventEngine = value;
}

