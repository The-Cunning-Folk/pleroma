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

GameObject &GameObjectFactory::buildGameObjectFromJson(rapidjson::Value & json)
{
    GameObject& entity = newObject();
    buildGameObjectComponentsFromJson(json,entity);
    return entity;
}

GameObject &GameObjectFactory::buildGameObjectFromJson(rapidjson::Value & json, std::string id)
{
    GameObject& entity = newObject(id);
    buildGameObjectComponentsFromJson(json,entity);
    return entity;
}

GameObject &GameObjectFactory::buildGameObjectComponentsFromJson(rapidjson::Value & json, GameObject & entity)
{
    if(json.HasMember("sprite"))
    {
        rapidjson::Value spr = json["sprite"].GetObject();
        SpriteRenderer & sprite = componentFactory->buildSpriteRendererFromJson(spr);
        entity.addComponent(sprite);
    }

    if(json.HasMember("hitbox"))
    {
        rapidjson::Value box = json["hitbox"].GetObject();
        Collidable & collidable = componentFactory->buildCollidableFromJson(box);
        entity.addComponent(collidable);
    }
    return entity;
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
    float sizeX = 24;
    float sizeY = 12;
    std::vector<sf::Vector2f> points;

    points.push_back(sf::Vector2f(-sizeX,-sizeY));
    points.push_back(sf::Vector2f(sizeX,-sizeY));
    points.push_back(sf::Vector2f(sizeX,sizeY));
    points.push_back(sf::Vector2f(-sizeX,sizeY));
    Collidable & hitbox = componentFactory->newCollidable(points);
    hitbox.setTransform(o.getTransform());
    hitbox.immovable = true;

    //temporary hardcode
    SpriteRenderer & sprite = componentFactory->newSpriteRenderer();
    sprite.spritesheet = "trees_1";
    sprite.clip = "big_tree";
    sprite.offset = sf::Vector2f(0,-48);
    sprite.depthOffset = 0;

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
    sprite.clip = "walk_down";
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
    sprite.spritesheet = "butterfly";
    sprite.animation.spf = 0.04f;
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
    Collidable & hitbox = componentFactory->newRectCollidable(sf::FloatRect(-2,-2,4,4));
    hitbox.setTransform(o.getTransform());
    hitbox.pathable = true;
    hitbox.immovable = false;
    hitbox.diminutive = true;
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


