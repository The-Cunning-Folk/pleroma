#include "gameobject.h"

using namespace BQ;

GameObject::GameObject()
{
    active = true;
}

void GameObject::deactivate()
{
    active = false;
}

void GameObject::activate()
{
    active = true;
}


std::map<std::string, std::map<std::string, int> > GameObject::getComponents() const
{
    return components;
}

int GameObject::getTransform() const
{
    return transform;
}

void GameObject::setTransform(int value)
{
    transform = value;
}

void GameObject::addComponent(Component& component)
{
    std::string name = component.name;
    if(name.compare("") != 0) //empty string safety
    {
        name = component.typeId + std::to_string(component.uniqueId);
    }
    addComponent(name,component);
}

void GameObject::addComponent(std::string name, Component & component)
{
    component.transform = this->transform;
    component.setParent(this->name);
    component.setName(name);
    components[component.typeId][name] = component.index;
}
