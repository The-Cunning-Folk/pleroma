#include "gameobject.h"

using namespace BQ;

GameObject::GameObject()
{

}

void GameObject::addComponent(Component* component)
{
    std::string name = component->name;
    if(name.compare("") != 0) //empty string safety
    {
        name = component->typeId + std::to_string(component->uniqueId);
    }
    components[name] = component;
}

void GameObject::update()
{

}



