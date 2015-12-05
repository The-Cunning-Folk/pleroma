#include "componentfactory.h"

ComponentFactory::ComponentFactory()
{

}

ComponentLoader *ComponentFactory::getComponentLoader() const
{
    return componentLoader;
}

void ComponentFactory::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}


BQ::Transform *ComponentFactory::newTransform()
{
    return transformEngine->addTransform();
}

Transform *ComponentFactory::newTransform(std::string name)
{
    Transform* transform = newTransform();
    transform->setName(name);
    return(transform);
}

Transform *ComponentFactory::newChildTransform(Transform* parent)
{
    Transform* transform = newTransform();
    parent->children.push_back(transform);
    return(transform);
}

PlayerInput *ComponentFactory::newPlayerInput()
{
    return inputEngine->addPlayerInput();
}

PlayerInput *ComponentFactory::newPlayerInput(std::string name)
{
    PlayerInput* input = newPlayerInput();
    input->setName(name);
    return(input);
}

GameLogic *ComponentFactory::newGameLogic()
{
    return eventEngine->addGameLogic();
}

GameLogic *ComponentFactory::newGameLogic(std::string name)
{
    GameLogic* gameLogic = newGameLogic();
    gameLogic->setName(name);
    gameLogic->setComponentLoader(componentLoader);
    return(gameLogic);
}

Collidable *ComponentFactory::newCollidable()
{
    return collisionEngine->addCollidable();
}

Collidable *ComponentFactory::newCollidable(std::string name)
{
    Collidable* collidable = collisionEngine->addCollidable();
    collidable->name = name;
    return(collidable);
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
