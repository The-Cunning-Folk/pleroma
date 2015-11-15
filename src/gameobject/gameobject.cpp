#include "gameobject.h"

GameObject::GameObject()
{

}

void GameObject::addComponent(Component* component)
{
    std::string name = component->name;
    if(name.compare("") != 0)
    {
        name = component->typeId + std::to_string(component->uniqueId);
    }

    components[component->name] = component;
}



