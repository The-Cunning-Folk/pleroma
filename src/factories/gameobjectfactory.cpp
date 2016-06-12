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
    return makePhysicsObject(collisionObj);
}

GameObject &GameObjectFactory::newImmovableObject()
{
    GameObject& o = newObject();
    float size = 16;
    std::vector<sf::Vector2f> points;

    points.push_back(sf::Vector2f(-size,-size+4));
    points.push_back(sf::Vector2f(size,-size+4));
    points.push_back(sf::Vector2f(size,size-4));
    points.push_back(sf::Vector2f(-size,size-4));
    Collidable & hitbox = componentFactory->newCollidable(points);
    hitbox.setTransform(o.getTransform());
    hitbox.immovable = true;

    //temporary hardcode
    SpriteRenderer & sprite = componentFactory->newSpriteRenderer();
    sprite.spritesheet = "demo_blocks";
    sprite.offset = sf::Vector2f(0,-18);
    sprite.depthOffset = 10;

    sprite.setTransform(o.getTransform());
    o.addComponent("sprite",sprite);

    o.addComponent("hitbox",hitbox);
    hitbox.update();
    return o;
}

GameObject& GameObjectFactory::newPlayerObject() //builds behaviours for the player
{
    GameObject& player = newObject("player_1");
    PlayerInput& input = componentFactory->newPlayerInput("player_input");
    GameLogic& logic = componentFactory->newGameLogic("player_logic");


    RigidBody & body = componentFactory->newRigidBody("player_rigidbody");
    RayEmitter & rays = componentFactory->newRayEmitter("player_ray1");
    SpriteRenderer & sprite = componentFactory->newSpriteRenderer("player_spr");

    Collidable & hitbox = componentFactory->newCollidable("player_hitbox");
    hitbox.pathable = true;
    hitbox.setTransform(player.getTransform());

    float corners = 1.0f;
    float size = 4.0f;
    hitbox.polygon.addPoint(sf::Vector2f(size-corners,size));
    hitbox.polygon.addPoint(sf::Vector2f(size,size-corners));
    hitbox.polygon.addPoint(sf::Vector2f(size,-size+corners));
    hitbox.polygon.addPoint(sf::Vector2f(size-corners,-size));
    hitbox.polygon.addPoint(sf::Vector2f(-size+corners,-size));
    hitbox.polygon.addPoint(sf::Vector2f(-size,-size+corners));
    hitbox.polygon.addPoint(sf::Vector2f(-size,size-corners));
    hitbox.polygon.addPoint(sf::Vector2f(-size+corners,size));

    player.addComponent("hitbox",hitbox);
    hitbox.update();

    Collidable & attack = componentFactory->newCollidable("player_attack");

    attack.physical = false;
    attack.pathable = true;
    attack.setTransform(player.getTransform());
    attack.solid = false;
    player.addComponent("attack",attack);
    attack.update();


    body.setTransform(player.getTransform());
    sprite.setTransform(player.getTransform());

    sprite.spritesheet = "clo_walk";
    sprite.offset = sf::Vector2f(0,-6);

    //add components
    player.addComponent("input",input);
    player.addComponent("logic",logic);


    player.addComponent("body",body);
    player.addComponent("raytest",rays);
    player.addComponent("sprite",sprite);

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
    GameObject & seeker = makePlayerSeekingObject(
                makePathingObject(
                    newObject()
                    )
                );

    SpriteRenderer & sprite = componentFactory->newSpriteRenderer("enemy_spr");
    sprite.setTransform(seeker.transform);
    seeker.addComponent(sprite);

    return seeker;
}

GameObject &GameObjectFactory::newPathingObject(std::string name)
{
    GameObject & seeker = makePlayerSeekingObject(
                makePathingObject(
                    newObject(name)
                    )
                );
    return seeker;
}

GameObject &GameObjectFactory::makePhysicsObject(GameObject & o)
{
    Collidable & hitbox = componentFactory->newRandomCollidable();
    hitbox.setTransform(o.getTransform());

    RigidBody & body = componentFactory->newRigidBody();
    body.restitution = maths->randomFloat(0.5,0.999);
    body.friction = 1E-10;
    body.setMass(maths->randomFloat(5,50));
    float momR = body.getMass()*500;
    body.momentum = sf::Vector2f(maths->randomFloat(-momR,momR),maths->randomFloat(-momR,momR));
    body.setTransform(o.getTransform());


    o.addComponent("hitbox",hitbox);
    o.addComponent("body",body);

    hitbox.update();
    return o;
}

GameObject &GameObjectFactory::makePathingObject(GameObject & o)
{
    Collidable & hitbox = componentFactory->newRandomCollidable();
    hitbox.setTransform(o.getTransform());
    hitbox.pathable = true;
    hitbox.immovable = false;
    hitbox.diminutive = false;
    hitbox.opaque = false;


    GameLogic& logic = componentFactory->newGameLogic();

    o.addComponent(hitbox);
    o.addComponent(logic);

    Behaviour & b = componentFactory->bindBehaviour(logic,"flowPathingBehaviours");

    return o;
}

GameObject &GameObjectFactory::makePlayerSeekingObject(GameObject & o)
{
    RayEmitter & e = componentFactory->newRayEmitter();
    e.addTarget("player_1");
    o.addComponent(e);
    return o;
}

