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

Behaviour &ComponentLoader::getBehaviour(int index)
{
    return logicEngine->getBehaviour(index);
}

RayEmitter &ComponentLoader::getRayEmitter(int index)
{
    return rayCastingEngine->getRayEmitter(index);
}

SpriteRenderer &ComponentLoader::getSpriteRenderer(int index)
{
    return renderEngine->getSpriteRenderer(index);
}

Transform &ComponentLoader::getTransformFromObject(GameObject & o, std::string name)
{
    Transform & t = getTransform(o.components["transform"][name]);
    return t;
}

Collidable &ComponentLoader::getCollidableFromObject(GameObject & o, std::string name)
{
    return getCollidable(o.components["collidable"][name]);
}

RigidBody &ComponentLoader::getRigidBodyFromObject(GameObject & o, std::string name)
{
    return getRigidBody(o.components["rigidbody"][name]);
}

GameLogic &ComponentLoader::getGameLogicFromObject(GameObject & o, std::string name)
{
    return getGameLogic(o.components["gamelogic"][name]);
}

RayEmitter &ComponentLoader::getRayEmitterFromObject(GameObject & o, std::string name)
{
    return getRayEmitter(o.components["rayemitter"][name]);
}

SpriteRenderer &ComponentLoader::getSpriteRendererFromObject(GameObject & o, std::string name)
{
    return getSpriteRenderer(o.components["spriterenderer"][name]);
}

std::vector<int> ComponentLoader::getComponentsFromObject(GameObject & o, std::string type)
{
    std::map<std::string,int> cs = o.components[type];
    return getIndicesFromMap(cs);
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

std::vector<int> ComponentLoader::getRayEmittersFromObject(GameObject & o)
{
    std::map<std::string,int> cs = o.components["rayemitter"];
    return getIndicesFromMap(cs);
}

std::vector<int> ComponentLoader::getSpriteRenderersFromObject(GameObject & o)
{
    std::map<std::string,int> cs = o.components["spriterenderer"];
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

LogicEngine *ComponentLoader::getLogicEngine() const
{
    return logicEngine;
}

void ComponentLoader::setLogicEngine(LogicEngine *value)
{
    logicEngine = value;
}

RenderEngine *ComponentLoader::getRenderEngine() const
{
    return renderEngine;
}

void ComponentLoader::setRenderEngine(RenderEngine *value)
{
    renderEngine = value;
}

RaycastingEngine *ComponentLoader::getRayCastingEngines() const
{
    return rayCastingEngine;
}

void ComponentLoader::setRayCastingEngines(RaycastingEngine *value)
{
    rayCastingEngine = value;
}

