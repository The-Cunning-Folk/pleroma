#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <factory.h>
#include <component.h>
#include <transform.h>
#include <gameobject.h>
#include <gameobjectpattern.h>

#include <transformengine.h>
#include <inputengine.h>
#include <eventengine.h>
#include <collisionengine.h>
#include <physicsengine.h>
#include <logicengine.h>
#include <raycastingengine.h>
#include <renderengine.h>

#include <datafileparser.h>

#include <componentloader.h>
#include <gameobjectloader.h>
#include <grid.h>

#include<gameobjectstore.h>

using namespace BQ;

class ComponentFactory : public Factory
{
public:
    ComponentFactory();

    DataFileParser dataFileParser;

    ComponentLoader* componentLoader;
    GameObjectLoader* gameObjectLoader;

    void buildCollidableFromPattern(CollidablePattern &, Collidable &);
    void buildSpriteRendererFromPattern(SpriteRendererPattern &, SpriteRenderer &);
    void buildRigidBodyFromPattern(RigidBodyPattern &, RigidBody &);
    void buildRayEmitterFromPattern(RayEmitterPattern &, RayEmitter &);
    void buildGameLogicFromPattern(GameLogicPattern &, GameLogic &);

    Behaviour& bindBehaviour(GameObjectStore &,GameLogic &, std::string);

    Transform& newTransform(GameObjectStore &);
    Transform& newTransform(GameObjectStore &,std::string);
    Transform& newChildTransform(GameObjectStore &,Transform&);

    //creation methods
    Collidable& newCollidable(GameObjectStore &);
    Collidable& newCollidable(GameObjectStore &,std::string);

    Collidable& newCollidable(GameObjectStore &,std::vector<sf::Vector2f>);
    Collidable& newCollidable(GameObjectStore &,std::string,std::vector<sf::Vector2f>);

    PlayerInput& newPlayerInput(GameObjectStore &);
    PlayerInput& newPlayerInput(GameObjectStore &,std::string);

    GameLogic& newGameLogic(GameObjectStore &);
    GameLogic& newGameLogic(GameObjectStore &, std::string);

    RigidBody& newRigidBody(GameObjectStore &);
    RigidBody& newRigidBody(GameObjectStore &,std::string);

    RayEmitter & newRayEmitter(GameObjectStore &);
    RayEmitter & newRayEmitter(GameObjectStore &,std::string);

    SpriteRenderer & newSpriteRenderer(GameObjectStore &);
    SpriteRenderer & newSpriteRenderer(GameObjectStore &,std::string);

    //getters/setters

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);

    LogicEngine *getLogicEngine() const;
    void setLogicEngine(LogicEngine *value);


private:

    LogicEngine* logicEngine;


};

#endif // COMPONENTFACTORY_H
