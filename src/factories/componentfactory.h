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
    Grid* grid;

    void buildCollidableFromPattern(CollidablePattern &, Collidable &);
    void buildSpriteRendererFromPattern(SpriteRendererPattern &, SpriteRenderer &);
    void buildRigidBodyFromPattern(RigidBodyPattern &, RigidBody &);
    void buildRayEmitterFromPattern(RayEmitterPattern &, RayEmitter &);
    void buildGameLogicFromPattern(GameLogicPattern &, GameLogic &);

    Behaviour& bindBehaviour(GameLogic &, std::string);

    Transform& newTransform(GameObjectStore &);
    Transform& newTransform(GameObjectStore &,std::string);
    Transform& newChildTransform(GameObjectStore &,Transform&);

    //creation methods
    Collidable& newCollidable(GameObjectStore &);
    Collidable& newCollidable(GameObjectStore &,std::string);

    Collidable& newCollidable(GameObjectStore &,std::vector<sf::Vector2f>);
    Collidable& newCollidable(GameObjectStore &,std::string,std::vector<sf::Vector2f>);

    PlayerInput& newPlayerInput();
    PlayerInput& newPlayerInput(std::string);

    GameLogic& newGameLogic();
    GameLogic& newGameLogic(std::string);

    RigidBody& newRigidBody();
    RigidBody& newRigidBody(std::string);

    RayEmitter & newRayEmitter();
    RayEmitter & newRayEmitter(std::string);

    SpriteRenderer & newSpriteRenderer();
    SpriteRenderer & newSpriteRenderer(std::string);

    //getters/setters

    TransformEngine *getTransformEngine() const;
    void setTransformEngine(TransformEngine *value);

    InputEngine *getInputEngine() const;
    void setInputEngine(InputEngine *value);

    EventEngine *getEventEngine() const;
    void setEventEngine(EventEngine *value);

    CollisionEngine *getCollisionEngine() const;
    void setCollisionEngine(CollisionEngine *value);

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

    PhysicsEngine *getPhysicsEngine() const;
    void setPhysicsEngine(PhysicsEngine *value);

    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);

    Grid *getGrid() const;
    void setGrid(Grid *value);

    LogicEngine *getLogicEngine() const;
    void setLogicEngine(LogicEngine *value);

    RaycastingEngine *getRayCastingEngine() const;
    void setRayCastingEngine(RaycastingEngine *value);

    RenderEngine *getRenderEngine() const;
    void setRenderEngine(RenderEngine *value);



private:

    TransformEngine* transformEngine;
    InputEngine* inputEngine;
    EventEngine* eventEngine;
    CollisionEngine* collisionEngine;
    PhysicsEngine* physicsEngine;
    LogicEngine* logicEngine;
    RaycastingEngine* rayCastingEngine;
    RenderEngine* renderEngine;


};

#endif // COMPONENTFACTORY_H
