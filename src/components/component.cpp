#include "component.h"

#include <gameobject.h>

using namespace BQ;

Component::Component()
{

}

void Component::setParent(GameObject * gameObject)
{
    parent = gameObject;
}

void Component::setName(std::string value)
{
    name = value;
}

