#include "gameobjectfactory.h"

using namespace BQ;

GameObjectFactory::GameObjectFactory()
{

}

void GameObjectFactory::setStack(GameObjectStack * stack)
{
    gameObjects = stack;
}

ComponentFactory *GameObjectFactory::getComponentFactory() const
{
    return componentFactory;
}

void GameObjectFactory::setComponentFactory(ComponentFactory *value)
{
    componentFactory = value;
}



void GameObjectFactory::newObject()
{
    GameObject* object = gameObjects->addObject();
    object->setTransform(componentFactory->newTransform());
    debug->println("generated object: " + object->name);
}

