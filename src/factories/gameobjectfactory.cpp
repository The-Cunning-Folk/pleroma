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

GameObject* GameObjectFactory::newObject()
{
    GameObject* object = gameObjects->addObject();
    object->setTransform(componentFactory->newTransform());
    debug->println("generated object: " + object->name);
    return object;
}

GameObject* GameObjectFactory::newPlayerObject()
{
    GameObject* player = newObject();
    PlayerInput* input = componentFactory->newPlayerInput();
    player->addComponent("input",input);
    input->inputMap.setKeyInput("move_up",sf::Keyboard::W);
    input->inputMap.setKeyInput("move_left",sf::Keyboard::A);
    input->inputMap.setKeyInput("move_right",sf::Keyboard::D);
    input->inputMap.setKeyInput("move_down",sf::Keyboard::S);
    return player;
}

