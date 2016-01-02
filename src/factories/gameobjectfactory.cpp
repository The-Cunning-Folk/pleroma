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
    object->setTransform(componentFactory->newTransform().index);
    //debug->println("generated object: " + object->name);
    return object;
}

GameObject *GameObjectFactory::newObject(std::string name)
{
    GameObject* object = gameObjects->addObject(name);
    object->setTransform(componentFactory->newTransform().index);
    //debug->println("generated object: " + object->name);
    return object;
}

GameObject *GameObjectFactory::newCollisionObject()
{
    GameObject* collisionObj = newObject();

    //collisionObj->loadTransform().setVelocity(sf::Vector2f(maths->randomFloat(-20,20),maths->randomFloat(-20,20)));

    Collidable & hitbox = componentFactory->newRandomCollidable();
    hitbox.setTransform(collisionObj->getTransform());

    RigidBody & body = componentFactory->newRigidBody();
    body.setTransform(collisionObj->getTransform());

    collisionObj->addComponent("hitbox",hitbox);
    collisionObj->addComponent("body",body);

    hitbox.update();
    return collisionObj;
}

GameObject* GameObjectFactory::newPlayerObject() //builds behaviours for the player
{
    GameObject* player = newObject("player_1");
    PlayerInput& input = componentFactory->newPlayerInput("player_input");
    GameLogic& logic = componentFactory->newGameLogic("player_logic");
    Collidable & hitbox = componentFactory->newCollidable("player_hitbox");

    float corners = 3;
    float size = 8;

    hitbox.polygon.addPoint(sf::Vector2f(size-corners,size));
    hitbox.polygon.addPoint(sf::Vector2f(size,size-corners));
    hitbox.polygon.addPoint(sf::Vector2f(size,-size+corners));
    hitbox.polygon.addPoint(sf::Vector2f(size-corners,-size));
    hitbox.polygon.addPoint(sf::Vector2f(-size+corners,-size));
    hitbox.polygon.addPoint(sf::Vector2f(-size,-size+corners));
    hitbox.polygon.addPoint(sf::Vector2f(-size,size-corners));
    hitbox.polygon.addPoint(sf::Vector2f(-size+corners,size));

    //add components
    player->addComponent("input",input);
    player->addComponent("logic",logic);
    player->addComponent("hitbox",hitbox);

    //input
    input.inputMap.setKeyInput("move_up",sf::Keyboard::W);
    input.inputMap.setKeyInput("move_left",sf::Keyboard::A);
    input.inputMap.setKeyInput("move_right",sf::Keyboard::D);
    input.inputMap.setKeyInput("move_down",sf::Keyboard::S);

    //behaviours
    logic.addBehaviour(new PlayerBehaviours);

    //collidable
    hitbox.setTransform(player->getTransform());
    //hitbox->setBBox(sf::FloatRect(-10,-10,20,20));

    return player;
}

