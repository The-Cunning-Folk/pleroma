#include "gameobject.h"

using namespace BQ;

GameObject::GameObject()
{

}

Transform *GameObject::getTransform() const
{
    return transform;
}

void GameObject::setTransform(Transform *value)
{
    transform = value;
    transform->setParent(this);
}

void GameObject::addComponent(Component* component)
{
    std::string name = component->name;
    if(name.compare("") != 0) //empty string safety
    {
        name = component->typeId + std::to_string(component->uniqueId);
    }
    addComponent(name,component);
}

void GameObject::update()
{

}

void BQ::GameObject::addComponent(std::string name, BQ::Component * component)
{
    components[name] = component;
}
