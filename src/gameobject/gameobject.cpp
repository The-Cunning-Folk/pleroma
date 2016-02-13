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

Transform &GameObject::loadTransform()
{
    return componentLoader->getTransform(transform);
}

std::vector<int> GameObject::loadComponents(std::string type)
{
    return componentLoader->getComponentsFromObject(*this,type);
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
    component.setParent(this->name);
    component.setName(name);
    components[component.typeId][component.name] = component.index;
}
