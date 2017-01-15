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
    nBehaviour=0;
}

ComponentLoader *GameObjectStore::getComponentLoader() const
{
    return componentLoader;
}

void GameObjectStore::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

void GameObjectStore::removeTransform(int i)
{
    std::map<int,Transform>::iterator it = transforms.find(i);
    if(it != transforms.end())
    {
        transforms.erase(it);
    }
}

void GameObjectStore::removeCollidable(int i)
{
    std::map<int,Collidable>::iterator it = collidables.find(i);
    if(it != collidables.end())
    {
        collidables.erase(it);
    }
}

void GameObjectStore::removeGameLogic(int i)
{
    std::map<int,GameLogic>::iterator it = gamelogics.find(i);
    if(it != gamelogics.end())
    {
        gamelogics.erase(it);
    }
}

void GameObjectStore::removePlayerInput(int i)
{
    std::map<int,PlayerInput>::iterator it = playerInputs.find(i);
    if(it != playerInputs.end())
    {
        playerInputs.erase(it);
    }
}

void GameObjectStore::removeRayEmitter(int i)
{
    std::map<int,RayEmitter>::iterator it = rayEmitters.find(i);
    if(it != rayEmitters.end())
    {
        rayEmitters.erase(it);
    }
}

void GameObjectStore::removeRigidBody(int i)
{
    std::map<int,RigidBody>::iterator it = rigidBodies.find(i);
    if(it != rigidBodies.end())
    {
        rigidBodies.erase(it);
    }
}

void GameObjectStore::removeSpriteRenderer(int i)
{
    std::map<int,SpriteRenderer>::iterator it = spriteRenderers.find(i);
    if(it != spriteRenderers.end())
    {
        spriteRenderers.erase(it);
    }
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

GameObject &GameObjectStore::getObject(std::string s)
{
    std::map<std::string,GameObject>::iterator it = objects.find(s);
    if(it != objects.end())
    {
        return objects[s];
    }
    else
    {
        return nullObj;
    }
}

void GameObjectStore::removeObjectComponents(GameObject & o)
{
    removeTransform(o.transform);
    for(it_strint it = o.components["transform"].begin(); it != o.components["transform"].end(); it++) {
        removeTransform(it->second);
    }
    for(it_strint it = o.components["collidable"].begin(); it != o.components["collidable"].end(); it++) {
        removeCollidable(it->second);
    }
    for(it_strint it = o.components["rigidbody"].begin(); it != o.components["rigidbody"].end(); it++) {
        removeRigidBody(it->second);
    }
    for(it_strint it = o.components["gamelogic"].begin(); it != o.components["gamelogic"].end(); it++) {
        removeGameLogic(it->second);
    }
    for(it_strint it = o.components["rayemitter"].begin(); it != o.components["rayemitter"].end(); it++) {
        removeRayEmitter(it->second);
    }
    for(it_strint it = o.components["spriterenderer"].begin(); it != o.components["spriterenderer"].end(); it++) {
        removeSpriteRenderer(it->second);
    }

}

void GameObjectStore::removeObjectComponents(std::string s)
{
    removeObjectComponents(getObject(s));
}

void GameObjectStore::deactivateObjectComponents(GameObject & o)
{

    std::map<int,Transform>::iterator it_c = transforms.find(o.transform);
    if(it_c != transforms.end())
    {
        it_c->second.deactivate();
    }

    for(it_strint it = o.components["transform"].begin(); it != o.components["transform"].end(); it++) {
        std::map<int,Transform>::iterator it_c = transforms.find(it->second);
        if(it_c != transforms.end())
        {
            it_c->second.deactivate();
        }
    }
    for(it_strint it = o.components["collidable"].begin(); it != o.components["collidable"].end(); it++) {
        std::map<int,Collidable>::iterator it_c = collidables.find(it->second);
        if(it_c != collidables.end())
        {
            it_c->second.deactivate();
        }
    }
    for(it_strint it = o.components["rigidbody"].begin(); it != o.components["rigidbody"].end(); it++) {
        std::map<int,RigidBody>::iterator it_c = rigidBodies.find(it->second);
        if(it_c != rigidBodies.end())
        {
            it_c->second.deactivate();
        }
    }
    for(it_strint it = o.components["gamelogic"].begin(); it != o.components["gamelogic"].end(); it++) {
        std::map<int,GameLogic>::iterator it_c = gamelogics.find(it->second);
        if(it_c != gamelogics.end())
        {
            it_c->second.deactivate();
        }
    }
    for(it_strint it = o.components["rayemitter"].begin(); it != o.components["rayemitter"].end(); it++) {
        std::map<int,RayEmitter>::iterator it_c = rayEmitters.find(it->second);
        if(it_c != rayEmitters.end())
        {
            it_c->second.deactivate();
        }
    }
    for(it_strint it = o.components["spriterenderer"].begin(); it != o.components["spriterenderer"].end(); it++) {
        std::map<int,SpriteRenderer>::iterator it_c = spriteRenderers.find(it->second);
        if(it_c != spriteRenderers.end())
        {
            it_c->second.deactivate();
        }
    }
}

void GameObjectStore::removeObject(GameObject & g)
{
    removeObject(g.name);
}

void GameObjectStore::removeObject(std::string s)
{
    std::map<std::string,GameObject>::iterator it = objects.find(s);
    if(it != objects.end())
    {
       //element found;
        removeObjectComponents(objects[s]);
        objects.erase(it);
    }
}

void GameObjectStore::deactivateObject(std::string s)
{
    deactivateObject(getObject(s));
}

void GameObjectStore::activateObject(std::string s)
{
    activateObject(getObject(s));
}

void GameObjectStore::deactivateObject(GameObject & o)
{
    o.deactivate();
}

void GameObjectStore::activateObject(GameObject & o)
{
    o.activate();
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

GameLogic &GameObjectStore::addGameLogic()
{
    nGameLogic++;
    GameLogic g;
    g.index=nGameLogic;
    return gamelogics[nGameLogic]=g;
}

PlayerInput &GameObjectStore::addPlayerInput()
{
    nPlayerInput++;
    PlayerInput p;
    p.index=nPlayerInput;
    return playerInputs[nPlayerInput]=p;
}

RayEmitter &GameObjectStore::addRayEmitter()
{
    nRayEmitter++;
    RayEmitter r;
    r.index=nRayEmitter;
    return rayEmitters[nRayEmitter]=r;
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

Transform &GameObjectStore::getTransform(int key)
{
    return transforms.count(key) ? transforms[key] : nullTransform;
}

Collidable &GameObjectStore::getCollidable(int key)
{
    return collidables.count(key) ? collidables[key] : nullCollidable;
}

GameLogic &GameObjectStore::getGameLogic(int key)
{
    return gamelogics.count(key) ? gamelogics[key] : nullLogic;
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

