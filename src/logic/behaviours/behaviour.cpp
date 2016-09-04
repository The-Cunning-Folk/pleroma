#include "behaviour.h"

#include<gameobject.h>
#include<game.h>

using namespace BQ;

Behaviour::Behaviour()
{

}

Game *Behaviour::getGame() const
{
    return game;
}

void Behaviour::setGame(Game *value)
{
    game = value;
}

float Behaviour::getDelta() const
{
    return delta;
}

void Behaviour::setDelta(float value)
{
    delta = value;
}

void Behaviour::addEvent(Event event)
{
    events.push_back(event);
}

void Behaviour::resolveEvents()
{
    beforeEvents();
    for(int i=0; i<events.size(); i++)
    {
        Event & e = events[i];
        resolveEvent(e);
    }
}

void Behaviour::beforeEvents()
{
    //nothing, put variable resets in here etc
}

void Behaviour::resolveEvent(Event &)
{
    //nothing!
}

void Behaviour::clearEvents()
{
    events.clear();
}

void Behaviour::update()
{

}

void Behaviour::collisionWith(GameObject & o, std::string me, std::string them)
{

}

bool Behaviour::compare(std::string big_s, std::string sub_s)
{
    return big_s.compare(sub_s)==0;
}

