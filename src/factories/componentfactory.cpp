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


BQ::Transform & ComponentFactory::newTransform()
{
    return transformEngine->addTransform();
}

Transform &ComponentFactory::newTransform(std::string name)
{
    Transform & transform = newTransform();
    transform.setName(name);
    return(transform);
}

Transform &ComponentFactory::newChildTransform(Transform& parent)
{
    Transform & transform = newTransform();
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
    gameLogic.setComponentLoader(componentLoader);
    gameLogic.setGameObjectLoader(gameObjectLoader);
    gameLogic.setMaths(maths);
    gameLogic.setDebug(debug);
    gameLogic.setGrid(grid);
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

Collidable & ComponentFactory::newCollidable()
{
    Collidable & c = collisionEngine->addCollidable();
    c.setComponentLoader(componentLoader);
    c.setGameObjectLoader(gameObjectLoader);
    c.setMaths(maths);
    c.setDebug(debug);
    c.setGrid(grid);
    return c;
}

Collidable & ComponentFactory::newCollidable(std::string name)
{
    Collidable & c = newCollidable();
    c.name = name;
//    c.polygon.points.push_back(sf::Vector2f(10,-10));
//    c.polygon.points.push_back(sf::Vector2f(10,10));
//    c.polygon.points.push_back(sf::Vector2f(-10,10));
//    c.polygon.points.push_back(sf::Vector2f(-10,-10));
    return(c);
}


Collidable &ComponentFactory::newRectCollidable(sf::FloatRect r)
{
    Collidable & c = newCollidable();
    c.polygon.addPoint(sf::Vector2f(r.left,r.top));
    c.polygon.addPoint(sf::Vector2f(r.left + r.width, r.top));
    c.polygon.addPoint(sf::Vector2f(r.left+r.width,r.top+r.height));
    c.polygon.addPoint(sf::Vector2f(r.left, r.top+r.height));
    return c;
}

Collidable &ComponentFactory::newRandomCollidable()
{
    float r = maths->randomFloat(1,10);
    return newRandomCollidable(r);
}

Collidable &ComponentFactory::newRandomCollidable(float r)
{

    Collidable & c = newCollidable();

    sf::Vector2f point;
    float a = 0.0;

    while(a<360.0)
    {
        point.x = r*maths->fcosDeg(a);
        point.y = r*maths->fsinDeg(a);
        c.polygon.addPoint(point);
        a += maths->randomFloat(10,80);
    }

    return c;
}

Collidable &ComponentFactory::newCollidable(std::vector<sf::Vector2f> points)
{
    if(points.size() < 2){
        debug->println("requested a collidable with only one point, returning a random");
        return newRandomCollidable();
    }

    Collidable & c = newCollidable();

    for(int i=0; i<points.size(); i++)
    {
        c.polygon.addPoint(points[i]);
    }
    return c;
}

RigidBody &ComponentFactory::newRigidBody()
{
    RigidBody & rigidBody = physicsEngine->addRigidBody();
    rigidBody.setComponentLoader(componentLoader);
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
