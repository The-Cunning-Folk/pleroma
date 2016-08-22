#ifndef GAMEOBJECTSTORE_H
#define GAMEOBJECTSTORE_H

#include <gameobject.h>
#include <componentloader.h>
#include <iostream>
#include <vector>
#include<functional>
#include<memory>
#include <map>

namespace BQ{
class GameObjectStore
{
public:
    GameObjectStore();

    ComponentLoader* componentLoader;

    GameObject& addObject();
    GameObject& addObject(std::string);

    std::map<std::string,GameObject> objects;

    std::map<int,Transform> transforms;
    std::map<int,Collidable> collidables;
    std::map<int,GameLogic> gamelogics;
    std::map<int,PlayerInput> playerInputs;
    std::map<int,RayEmitter> rayEmitters;
    std::map<int,RigidBody> rigidBodies;
    std::map<int,SpriteRenderer> spriteRenderers;

    int nTransform,nCollidable,nGameLogic,nPlayerInput,nRayEmitter,nRigidBody,nSpriteRenderer;

    Transform & addTransform();

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

private:

    GameObject& generateObject(std::string);

    std::string placeholder;
    int currentId;

};
}
#endif // GAMEOBJECTSTACK_H
