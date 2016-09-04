#include "gameobjectstore.h"

using namespace BQ;

GameObjectStore::GameObjectStore()
{
    placeholder = "auto_obj_";
    currentId = 1;
    nTransform=0;
    nCollidable=0;
    nGameLogic=0;
    nPlayerInput=0;
    nRigidBody=0;
    nRayEmitter=0;
    nSpriteRenderer=0;
}

ComponentLoader *GameObjectStore::getComponentLoader() const
{
    return componentLoader;
}

void GameObjectStore::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}


GameObject & GameObjectStore::addObject()
{
    std::string name = placeholder + std::to_string(currentId);
    return addObject(name);
}

GameObject & GameObjectStore::addObject(std::string name)
{
    return generateObject(name);
}

Transform & GameObjectStore::addTransform()
{
    nTransform++;
    Transform t;
    t.index=nTransform;
    return transforms[nTransform]=t;
}

Collidable &GameObjectStore::addCollidable()
{
    nCollidable++;
    Collidable c;
    c.index=nCollidable;
    return collidables[nCollidable]=c;
}

PlayerInput &GameObjectStore::addPlayerInput()
{
    nPlayerInput++;
    PlayerInput p;
    p.index=nPlayerInput;
    return playerInputs[nPlayerInput]=p;
}

RigidBody &GameObjectStore::addRigidBody()
{
    nRigidBody++;
    RigidBody r;
    r.index=nRigidBody;
    return rigidBodies[nRigidBody]=r;
}

SpriteRenderer &GameObjectStore::addSpriteRenderer()
{
    nSpriteRenderer++;
    SpriteRenderer s;
    s.index=nSpriteRenderer;
    return spriteRenderers[nSpriteRenderer]=s;
}

GameObject& GameObjectStore::generateObject(std::string name)
{
    GameObject object;
    object.name = name;
    object.uniqueId = currentId;
    objects[object.name] = object;
    currentId++;
    return(objects[name]);
}

