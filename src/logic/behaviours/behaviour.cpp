#include "behaviour.h"

#include<gameobject.h>
#include<componentloader.h>
#include<gameobjectloader.h>

using namespace BQ;

Behaviour::Behaviour()
{

}

Grid *Behaviour::getGrid() const
{
    return grid;
}

void Behaviour::setGrid(Grid *value)
{
    grid = value;
}

DebugUtils *Behaviour::getDebug() const
{
    return debug;
}

void Behaviour::setDebug(DebugUtils *value)
{
    debug = value;
}

MathsUtils *Behaviour::getMaths() const
{
    return maths;
}

void Behaviour::setMaths(MathsUtils *value)
{
    maths = value;
}

GameObjectLoader *Behaviour::getGameObjectLoader() const
{
    return gameObjectLoader;
}

void Behaviour::setGameObjectLoader(GameObjectLoader *value)
{
    gameObjectLoader = value;
}

ComponentLoader *Behaviour::getComponentLoader() const
{
    return componentLoader;
}

void Behaviour::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
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

