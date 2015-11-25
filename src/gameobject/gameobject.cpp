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
    value->setParent(this);
    transform = value;
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
    component->setParent(this);
    components[component->typeId][name] = component;
}

Component *GameObject::getComponentByName(std::string name)
{
    std::map<std::string,std::map<std::string,Component*>>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        std::map<std::string,Component*>& types = it->second;
        if(types[name] != NULL){
            return types[name];
        }
    }
    return NULL;
}

std::map<std::string, Component *> GameObject::getComponentsByType(std::string type)
{
    return components[type];
}

