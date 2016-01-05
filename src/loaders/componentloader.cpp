#include "componentloader.h"

#include <gameobject.h>
#include <eventengine.h>
#include <gameobjectloader.h>

using namespace BQ;
ComponentLoader::ComponentLoader()
{

}

Transform & ComponentLoader::getTransform(int index)
{
    return transformEngine->getTransform(index);
}

Collidable &ComponentLoader::getCollidable(int index)
{
    return collisionEngine->getCollidable(index);
}

RigidBody &ComponentLoader::getRigidBody(int index)
{
    return physicsEngine->getRigidBody(index);
}

GameLogic &ComponentLoader::getGameLogic(int index)
{
    return eventEngine->getGameLogic(index);
}

Collidable &ComponentLoader::getCollidableFromObject(GameObject & o, std::string name)
{
    Collidable & c = getCollidable(o.components["collidable"][name]);
    return c;
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

std::vector<int> ComponentLoader::getInputsFromObject(GameObject & o)
{
    std::map<std::string,int> cs = o.components["input"];
    return getIndicesFromMap(cs);
}

std::vector<int> ComponentLoader::getRigidBodiesFromObject(GameObject & o)
{
    std::map<std::string,int> cs = o.components["rigidbody"];
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

PhysicsEngine *ComponentLoader::getPhysicsEngine() const
{
    return physicsEngine;
}

void ComponentLoader::setPhysicsEngine(PhysicsEngine *value)
{
    physicsEngine = value;
}

EventEngine *ComponentLoader::getEventEngine() const
{
    return eventEngine;
}

void ComponentLoader::setEventEngine(EventEngine *value)
{
    eventEngine = value;
}

GameObjectLoader *ComponentLoader::getGameObjectLoader() const
{
    return gameObjectLoader;
}

void ComponentLoader::setGameObjectLoader(GameObjectLoader *value)
{
    gameObjectLoader = value;
}

