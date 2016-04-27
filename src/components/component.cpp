#include "component.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;

Component::Component()
{
}


Grid *Component::getGrid() const
{
    return grid;
}

void Component::setGrid(Grid *value)
{
    grid = value;
}

MathsUtils *Component::getMaths() const
{
    return maths;
}

void Component::setMaths(MathsUtils *value)
{
    maths = value;
}

GameObjectLoader *Component::getGameObjectLoader() const
{
    return gameObjectLoader;
}

void Component::setGameObjectLoader(GameObjectLoader *value)
{
    gameObjectLoader = value;
}

ComponentLoader *Component::getComponentLoader() const
{
    return componentLoader;
}

void Component::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

std::string Component::getParent() const
{
    return parent;
}

void Component::setParent(const std::string &value)
{
    parent = value;
}

DebugUtils *Component::getDebug() const
{
    return debug;
}

void Component::setDebug(DebugUtils *value)
{
    debug = value;
}


void Component::setName(std::string value)
{
    name = value;
}

