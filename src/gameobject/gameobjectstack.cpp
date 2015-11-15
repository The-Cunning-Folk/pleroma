#include "gameobjectstack.h"

using namespace BQ;

GameObjectStack::GameObjectStack()
{
    placeholder = "auto_obj_";
    currentId = 1;
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
    object.name = name;
    object.uniqueId = currentId;
    objects[object.name] = object;
    currentId++;
    return(&objects[name]);
}

