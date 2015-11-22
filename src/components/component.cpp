#include "component.h"

#include <gameobject.h>

using namespace BQ;

Component::Component()
{

}

DebugUtils *Component::getDebug() const
{
    return debug;
}

void Component::setDebug(DebugUtils *value)
{
    debug = value;
}


void Component::setParent(GameObject * gameObject)
{
    parent = gameObject;
}

void Component::setName(std::string value)
{
    name = value;
}

