#include "component.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>
#include <transform.h>

using namespace BQ;

Component::Component()
{
}

int Component::getTransform() const
{
    return transform;
}

void Component::setTransform(int value)
{
    transform = value;
}


std::string Component::getParent() const
{
    return parent;
}

void Component::setParent(const std::string &value)
{
    parent = value;
}


void Component::setName(std::string value)
{
    name = value;
}

