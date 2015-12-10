#include "gameobject.h"

using namespace BQ;

GameObject::GameObject()
{

}

ComponentLoader *GameObject::getComponentLoader() const
{
    return componentLoader;
}

void GameObject::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

int GameObject::getTransform() const
{
    return transform;
}

void GameObject::setTransform(int value)
{
    transform = value;
}

void GameObject::setPosition(sf::Vector2f pos)
{
    //    transform->setPosition(pos);
}

Transform &GameObject::loadTransform()
{
    return componentLoader->getTransform(transform);
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
    component.setParent(this);
    components[component.typeId][component.name] = component.index;
}

void GameObject::update()
{

}
