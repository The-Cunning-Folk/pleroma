#include "componentfactory.h"

#include <game.h>

ComponentFactory::ComponentFactory()
{

}

void ComponentFactory::buildCollidableFromPattern(CollidablePattern & pattern, Collidable & c)
{
    c.name = pattern.name;
    c.immovable = pattern.immovable;
    c.solid = pattern.solid;
    c.pathable = pattern.pathable;
    c.opaque = pattern.opaque;
    c.diminutive = pattern.diminutive;
    for(int i=0; i<pattern.polygon.size(); i++)
    {
        c.polygon.addPoint(pattern.polygon[i]);
    }
}

void ComponentFactory::buildSpriteRendererFromPattern(SpriteRendererPattern & pattern, SpriteRenderer & s)
{
    s.name = pattern.name;
    s.spritesheet = pattern.sheet;
    s.depthOffset = pattern.depthOffset;
    s.clip = pattern.clip;
    s.offset = pattern.offset;
    if(pattern.paused)
    {
        s.animation.stop();
    }
    else
    {
        s.animation.play();
    }
    s.animation.spf = pattern.spf;
}

void ComponentFactory::buildRigidBodyFromPattern(RigidBodyPattern & pattern, RigidBody & r)
{
    r.setMass(pattern.mass);
    r.name = pattern.name;
    r.restitution = pattern.restitution;
    r.friction = pattern.friction;
    r.momentum = pattern.momentum;
}


void ComponentFactory::buildRayEmitterFromPattern(BQ::RayEmitterPattern & pattern, BQ::RayEmitter & r)
{
    r.name = pattern.name;
    for(int i = 0; i<pattern.targets.size(); i++)
    {
        r.addTarget(pattern.targets[i]);
    }
    for(int i=0; i<pattern.positions.size(); i++)
    {
        r.positions.push_back(pattern.positions[i]);
    }
}

void ComponentFactory::buildGameLogicFromPattern(GameLogicPattern & pattern, GameLogic & g)
{
    g.name = pattern.name;
}

Grid *ComponentFactory::getGrid() const
{
    return grid;
}

void ComponentFactory::setGrid(Grid *value)
{
    grid = value;
}

LogicEngine *ComponentFactory::getLogicEngine() const
{
    return logicEngine;
}

void ComponentFactory::setLogicEngine(LogicEngine *value)
{
    logicEngine = value;
}

RaycastingEngine *ComponentFactory::getRayCastingEngine() const
{
    return rayCastingEngine;
}

void ComponentFactory::setRayCastingEngine(RaycastingEngine *value)
{
    rayCastingEngine = value;
}

RenderEngine *ComponentFactory::getRenderEngine() const
{
    return renderEngine;
}

void ComponentFactory::setRenderEngine(RenderEngine *value)
{
    renderEngine = value;
}

GameObjectLoader *ComponentFactory::getGameObjectLoader() const
{
    return gameObjectLoader;
}

void ComponentFactory::setGameObjectLoader(GameObjectLoader *value)
{
    gameObjectLoader = value;
}

ComponentLoader *ComponentFactory::getComponentLoader() const
{
    return componentLoader;
}

void ComponentFactory::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

PhysicsEngine *ComponentFactory::getPhysicsEngine() const
{
    return physicsEngine;
}

void ComponentFactory::setPhysicsEngine(PhysicsEngine *value)
{
    physicsEngine = value;
}


BQ::Transform & ComponentFactory::newTransform(GameObjectStore & s)
{
    return s.addTransform();
}

Transform &ComponentFactory::newTransform(GameObjectStore & s, std::string name)
{
    Transform & transform = newTransform(s);
    transform.setName(name);
    return(transform);
}

Transform &ComponentFactory::newChildTransform(GameObjectStore & s,Transform& parent)
{
    Transform & transform = newTransform(s);
    parent.children.push_back(transform.index);
    return(transform);
}

PlayerInput &ComponentFactory::newPlayerInput()
{
    return inputEngine->addPlayerInput();
}

PlayerInput &ComponentFactory::newPlayerInput(std::string name)
{
    PlayerInput & input = newPlayerInput();
    input.setName(name);
    return(input);
}

GameLogic &ComponentFactory::newGameLogic()
{
    GameLogic& gameLogic = eventEngine->addGameLogic();
    return gameLogic;
}

GameLogic &ComponentFactory::newGameLogic(std::string name)
{
    GameLogic& gameLogic = newGameLogic();
    gameLogic.setName(name);
    return(gameLogic);
}

Behaviour &ComponentFactory::bindBehaviour(GameLogic & g, std::string type)
{
    return logicEngine->bindBehaviour(g,type);
}

Collidable & ComponentFactory::newCollidable(GameObjectStore & s)
{
    Collidable & c = s.addCollidable();
    return c;
}

Collidable & ComponentFactory::newCollidable(GameObjectStore & s,std::string name)
{
    Collidable & c = newCollidable(s);
    c.name = name;
    return(c);
}

Collidable &ComponentFactory::newCollidable(GameObjectStore & s,std::vector<sf::Vector2f> points)
{
    Collidable & c = newCollidable(s);

    for(int i=0; i<points.size(); i++)
    {
        c.polygon.addPoint(points[i]);
    }
    return c;
}

RigidBody &ComponentFactory::newRigidBody()
{
    RigidBody & rigidBody = physicsEngine->addRigidBody();
    return rigidBody;
}

RigidBody &ComponentFactory::newRigidBody(std::string name)
{
    RigidBody & rigidBody = newRigidBody();
    rigidBody.setName(name);
    return rigidBody;
}

RayEmitter &ComponentFactory::newRayEmitter()
{
    return rayCastingEngine->addRayEmitter();
}

RayEmitter &ComponentFactory::newRayEmitter(std::string name)
{
    RayEmitter & rayEmitter = rayCastingEngine->addRayEmitter();
    rayEmitter.setName(name);
    return rayEmitter;
}

SpriteRenderer &ComponentFactory::newSpriteRenderer()
{
    return renderEngine->addSpriteRenderer();
}

SpriteRenderer &ComponentFactory::newSpriteRenderer(std::string name)
{
    SpriteRenderer & spriteRenderer = renderEngine->addSpriteRenderer();
    spriteRenderer.setName(name);
    return spriteRenderer;
}

TransformEngine *ComponentFactory::getTransformEngine() const
{
    return transformEngine;
}

void ComponentFactory::setTransformEngine(TransformEngine *value)
{
    transformEngine = value;
}

InputEngine *ComponentFactory::getInputEngine() const
{
    return inputEngine;
}

void ComponentFactory::setInputEngine(InputEngine *value)
{
    inputEngine = value;
}

EventEngine *ComponentFactory::getEventEngine() const
{
    return eventEngine;
}

void ComponentFactory::setEventEngine(EventEngine *value)
{
    eventEngine = value;
}

CollisionEngine *ComponentFactory::getCollisionEngine() const
{
    return collisionEngine;
}

void ComponentFactory::setCollisionEngine(CollisionEngine *value)
{
    collisionEngine = value;
}

