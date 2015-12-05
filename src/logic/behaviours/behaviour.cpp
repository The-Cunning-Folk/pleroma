#include "behaviour.h"

#include<gameobject.h>
using namespace BQ;

Behaviour::Behaviour()
{

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
    //nothing here...
}

void Behaviour::clearEvents()
{
    events.clear();
}

void Behaviour::update()
{
    resolveEvents();
    clearEvents();
}

