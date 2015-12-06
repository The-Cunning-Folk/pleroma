#include "componentloader.h"

using namespace BQ;
ComponentLoader::ComponentLoader()
{

}

Transform & ComponentLoader::getTransform(int index)
{
    return transformEngine->getTransform(index);
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

