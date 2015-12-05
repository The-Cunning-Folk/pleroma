#include "gameobjectstack.h"

using namespace BQ;

GameObjectStack::GameObjectStack()
{
    placeholder = "auto_obj_";
    currentId = 1;
}

ComponentLoader *GameObjectStack::getComponentLoader() const
{
    return componentLoader;
}

void GameObjectStack::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}


GameObject * GameObjectStack::addObject()
{
    std::string name = placeholder + std::to_string(currentId);
    return addObject(name);
}

GameObject * GameObjectStack::addObject(std::string name)
{
    return generateObject(name);
}

GameObject* GameObjectStack::generateObject(std::string name)
{
    GameObject object;
    object.setComponentLoader(componentLoader);
    object.name = name;
    object.uniqueId = currentId;
    objects[object.name] = object;
    currentId++;
    return(&objects[name]);
}

