#include "componentloader.h"

#include <gameobject.h>

using namespace BQ;
ComponentLoader::ComponentLoader()
{

}

Transform & ComponentLoader::getTransform(int index)
{
    return transformEngine->getTransform(index);
}

std::vector<int> ComponentLoader::getIndicesFromMap(std::map<std::string, int> cs)
{
    std::vector<int> indices;
    indices.resize(0);
    for(it iterator = cs.begin(); iterator != cs.end(); iterator++) {
        indices.push_back(iterator->second);
    }
    return indices;
}

std::vector<int> ComponentLoader::getCollidablesFromObject(GameObject & o)
{
    std::map<std::string,int> cs = o.components["collidable"];
    return getIndicesFromMap(cs);
}

std::vector<int> ComponentLoader::getGameLogicsFromObject(GameObject & o)
{
    std::map<std::string,int> cs = o.components["gamelogic"];
    return getIndicesFromMap(cs);
}

CollisionEngine *ComponentLoader::getCollisionEngine() const
{
    return collisionEngine;
}

void ComponentLoader::setCollisionEngine(CollisionEngine *value)
{
    collisionEngine = value;
}

InputEngine *ComponentLoader::getInputEngine() const
{
    return inputEngine;
}

void ComponentLoader::setInputEngine(InputEngine *value)
{
    inputEngine = value;
}

TransformEngine *ComponentLoader::getTransformEngine() const
{
    return transformEngine;
}

void ComponentLoader::setTransformEngine(TransformEngine *value)
{
    transformEngine = value;
}

