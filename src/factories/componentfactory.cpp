#include "componentfactory.h"

#include <game.h>

ComponentFactory::ComponentFactory()
{

}

Grid *ComponentFactory::getGrid() const
{
    return grid;
}

void ComponentFactory::setGrid(Grid *value)
{
    grid = value;
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

Collidable & ComponentFactory::newCollidable()
{
    Collidable& collidable = collisionEngine->addCollidable();
    collidable.setComponentLoader(componentLoader);
    collidable.setGameObjectLoader(gameObjectLoader);
    collidable.setMaths(maths);
    collidable.setDebug(debug);
    collidable.setGrid(grid);
    return collidable;
}

Collidable & ComponentFactory::newCollidable(std::string name)
{
    Collidable & collidable = newCollidable();
    collidable.name = name;
    return(collidable);
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
    Collidable & collidable = newCollidable();

    float r = maths->randomFloat(3,15);
    sf::Vector2f point;
    float a = 0.0;

    while(a<360.0)
    {
        point.x = r*maths->fcosDeg(a);
        point.y = r*maths->fsinDeg(a);
        collidable.polygon.addPoint(point);
        a += maths->randomFloat(10,80);
    }

    return collidable;
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
