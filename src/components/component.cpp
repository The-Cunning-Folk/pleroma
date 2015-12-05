#include "component.h"

#include <gameobject.h>
#include <componentloader.h>

using namespace BQ;

Component::Component()
{

}

ComponentLoader *Component::getComponentLoader() const
{
    return componentLoader;
}

void Component::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

DebugUtils *Component::getDebug() const
{
    return debug;
}

void Component::setDebug(DebugUtils *value)
{
    debug = value;
}

GameObject *Component::getParent() const
{
    return parent;
}


void Component::setParent(GameObject * gameObject)
{
    parent = gameObject;
}

void Component::setName(std::string value)
{
    name = value;
}

