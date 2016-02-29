#include "gameobjectfactory.h"

#include <game.h>

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

GameObject& GameObjectFactory::newObject()
{
    GameObject& object = gameObjects->addObject();
    Transform & t = componentFactory->newTransform();
    t.setParent(object.name);
    object.setTransform(t.index);
    //debug->println("generated object: " + object->name);
    return object;
}

GameObject &GameObjectFactory::newObject(std::string name)
{
    GameObject& object = gameObjects->addObject(name);
    Transform & t = componentFactory->newTransform();
    t.setParent(object.name);
    object.setTransform(t.index);
    //debug->println("generated object: " + object->name);
    return object;
}

GameObject &GameObjectFactory::newCollisionObject()
{
    GameObject& collisionObj = newObject();

    Collidable & hitbox = componentFactory->newRandomCollidable();
    hitbox.setTransform(collisionObj.getTransform());

    RigidBody & body = componentFactory->newRigidBody();
    body.restitution = maths->randomFloat(0.5,0.999);
    body.friction = 1E-10;
    body.setMass(maths->randomFloat(5,50));
    float momR = body.getMass()*500;
    body.momentum = sf::Vector2f(maths->randomFloat(-momR,momR),maths->randomFloat(-momR,momR));
    body.setTransform(collisionObj.getTransform());


    collisionObj.addComponent("hitbox",hitbox);
    collisionObj.addComponent("body",body);

    hitbox.update();
    return collisionObj;
}

GameObject &GameObjectFactory::newImmovableObject()
{
    GameObject& o = newObject();
    Collidable & hitbox = componentFactory->newRectCollidable(sf::FloatRect(-16,-16,32,32));
    hitbox.setTransform(o.getTransform());
    hitbox.immovable = true;
    o.addComponent("hitbox",hitbox);
    hitbox.update();
    return o;
}

GameObject& GameObjectFactory::newPlayerObject() //builds behaviours for the player
{
    GameObject& player = newObject("player_1");
    PlayerInput& input = componentFactory->newPlayerInput("player_input");
    GameLogic& logic = componentFactory->newGameLogic("player_logic");
    Collidable & hitbox = componentFactory->newCollidable("player_hitbox");
    Collidable & attack = componentFactory->newCollidable("player_attack");
    RigidBody & body = componentFactory->newRigidBody("player_rigidbody");

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

    hitbox.pathable = true;
    attack.physical = false;
    attack.pathable = true;


    hitbox.setTransform(player.getTransform());
    body.setTransform(player.getTransform());
    attack.setTransform(player.getTransform());

    attack.solid = false;

    //add components
    player.addComponent("input",input);
    player.addComponent("logic",logic);
    player.addComponent("hitbox",hitbox);
    player.addComponent("attack",attack);
    player.addComponent("body",body);

    //input
    input.inputMap.setKeyInput("move_up",sf::Keyboard::W);
    input.inputMap.setKeyInput("move_left",sf::Keyboard::A);
    input.inputMap.setKeyInput("move_right",sf::Keyboard::D);
    input.inputMap.setKeyInput("move_down",sf::Keyboard::S);
    input.inputMap.setKeyInput("attack",sf::Keyboard::L);
    input.inputMap.setKeyInput("roll",sf::Keyboard::Space);

    //behaviours

    Behaviour & b = componentFactory->bindBehaviour(logic,"playerBehaviours");

    //logic.addBehaviour(new PlayerBehaviours);

    //collidable
    body.friction = 0.1;
    body.setMass(3);

    return player;
}

GameObject &GameObjectFactory::newPathingObject()
{

    GameObject & seeker = newObject();

    Collidable & hitbox = componentFactory->newRandomCollidable();
    hitbox.setTransform(seeker.getTransform());
    hitbox.pathable = true;
    hitbox.immovable = false;
    hitbox.diminutive = true;


    GameLogic& logic = componentFactory->newGameLogic();



    //logic.addBehaviour(new FlowPathingBehaviours);

    seeker.addComponent(hitbox);
    seeker.addComponent(logic);

    Behaviour & b = componentFactory->bindBehaviour(logic,"flowPathingBehaviours");

    return seeker;
}

