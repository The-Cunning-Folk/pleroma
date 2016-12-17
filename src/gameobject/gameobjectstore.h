#ifndef GAMEOBJECTSTORE_H
#define GAMEOBJECTSTORE_H

#include <gameobject.h>
#include <componentloader.h>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <map>



namespace BQ{

typedef std::map<std::string, int>::iterator it_strint;
typedef std::map<std::string, GameObject>::iterator it_object;
typedef std::map<int, Transform>::iterator it_transform;
typedef std::map<int, Collidable>::iterator it_collidable;
typedef std::map<int, GameLogic>::iterator it_gamelogic;
typedef std::map<int, PlayerInput>::iterator it_playerinput;
typedef std::map<int, RayEmitter>::iterator it_rayemitter;
typedef std::map<int, RigidBody>::iterator it_rigidbody;
typedef std::map<int, SpriteRenderer>::iterator it_sprrenderer;

class GameObjectStore
{
public:
    GameObjectStore();

    GameObject nullObj;

    ComponentLoader* componentLoader;

    GameObject& addObject();
    GameObject& addObject(std::string);

    GameObject& getObject(std::string);

    void removeObjectComponents(GameObject &);
    void removeObjectComponents(std::string);

    void deactivateObjectComponents(GameObject &);

    void removeObject(GameObject&);
    void removeObject(std::string);

    void deactivateObject(std::string);
    void activateObject(std::string);

    void deactivateObject(GameObject &);
    void activateObject(GameObject &);

    std::map<std::string,GameObject> objects;

    std::map<int,Transform> transforms;
    std::map<int,Collidable> collidables;
    std::map<int,GameLogic> gamelogics;
    std::map<int,PlayerInput> playerInputs;
    std::map<int,RayEmitter> rayEmitters;
    std::map<int,RigidBody> rigidBodies;
    std::map<int,SpriteRenderer> spriteRenderers;

    int nTransform,nCollidable,nGameLogic,nPlayerInput,nRayEmitter,nRigidBody,nSpriteRenderer,nBehaviour;

    Transform & addTransform();
    Collidable & addCollidable();
    GameLogic & addGameLogic();
    PlayerInput & addPlayerInput();
    RayEmitter & addRayEmitter();
    RigidBody & addRigidBody();
    SpriteRenderer & addSpriteRenderer();

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

private:


    void removeTransform(int);
    void removeCollidable(int);
    void removeGameLogic(int);
    void removePlayerInput(int);
    void removeRayEmitter(int);
    void removeRigidBody(int);
    void removeSpriteRenderer(int);

    GameObject& generateObject(std::string);

    std::string placeholder;
    int currentId;

};
}
#endif // GAMEOBJECTSTACK_H
