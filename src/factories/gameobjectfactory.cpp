#include "gameobjectfactory.h"

#include <game.h>

using namespace BQ;

GameObjectFactory::GameObjectFactory()
{

}

GameObject &GameObjectFactory::buildGameObjectFromPattern(GameObjectStore & s, GameObjectPattern & pattern)
{
    GameObject & g = newObject(s);
    buildComponentsFromPattern(s,pattern,g);
    return g;
}

GameObject &GameObjectFactory::buildGameObjectFromPattern(GameObjectStore & s, GameObjectPattern & pattern, std::string id)
{
    GameObject & g = newObject(s,id);
    buildComponentsFromPattern(s,pattern,g);
    return g;
}

GameObject &GameObjectFactory::buildComponentsFromPattern(GameObjectStore & s, GameObjectPattern & pattern, GameObject & g)
{
    for(int i=0; i<pattern.spriteRendererPatterns.size(); i++)
    {
        SpriteRenderer & sp = componentFactory->newSpriteRenderer(s);
        componentFactory->buildSpriteRendererFromPattern(pattern.spriteRendererPatterns[i],sp);
        g.addComponent(sp.name,sp);
    }
    for(int i=0; i<pattern.collidablePatterns.size(); i++)
    {
        Collidable & c = componentFactory->newCollidable(s);
        componentFactory->buildCollidableFromPattern(pattern.collidablePatterns[i],c);
        g.addComponent(c.name,c);
    }
    for(int i=0; i<pattern.rigidBodyPatterns.size(); i++)
    {
        RigidBody & r = componentFactory->newRigidBody(s);
        componentFactory->buildRigidBodyFromPattern(pattern.rigidBodyPatterns[i],r);
        g.addComponent(r.name,r);
    }
    for(int i=0 ; i<pattern.rayEmitterPatterns.size(); i++)
    {
        RayEmitter & r = componentFactory->newRayEmitter(s);
        componentFactory->buildRayEmitterFromPattern(pattern.rayEmitterPatterns[i],r);
        g.addComponent(r.name,r);
    }
    for(int i=0 ; i<pattern.gameLogicPatterns.size(); i++)
    {
        GameLogic & l = componentFactory->newGameLogic(s);
        componentFactory->buildGameLogicFromPattern(pattern.gameLogicPatterns[i],l);
        g.addComponent(l.name,l);
        for(int j=0; j<pattern.gameLogicPatterns[i].behaviours.size(); j++)
        {
            std::string b = pattern.gameLogicPatterns[i].behaviours[j];
            componentFactory->bindBehaviour(s,l,b);
        }

    }
    return g;
}


ComponentFactory *GameObjectFactory::getComponentFactory() const
{
    return componentFactory;
}

void GameObjectFactory::setComponentFactory(ComponentFactory *value)
{
    componentFactory = value;
}

GameObject& GameObjectFactory::newObject(GameObjectStore & s)
{
    GameObject& object = s.addObject();
    Transform & t = componentFactory->newTransform(s);
    t.setParent(object.name);
    object.setTransform(t.index);
    return object;
}

GameObject &GameObjectFactory::newObject(GameObjectStore & s, std::string name)
{
    GameObject& object = s.addObject(name);
    Transform & t = componentFactory->newTransform(s);
    t.setParent(object.name);
    object.setTransform(t.index);
    return object;
}

GameObject& GameObjectFactory::newPlayerObject(GameObjectStore & s) //builds behaviours for the player
{
    GameObject& player = newObject(s, "player_1");
    PlayerInput& input = componentFactory->newPlayerInput(s,"player_input");
    GameLogic& logic = componentFactory->newGameLogic(s,"player_logic");


    RigidBody & body = componentFactory->newRigidBody(s,"player_rigidbody");
    RayEmitter & rays = componentFactory->newRayEmitter(s,"player_ray1");
    SpriteRenderer & sprite = componentFactory->newSpriteRenderer(s,"player_spr");

    Collidable & hitbox = componentFactory->newCollidable(s,"player_hitbox");
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

    Collidable & attack = componentFactory->newCollidable(s,"player_attack");

    attack.interactsWithPhysics = true;
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

    Behaviour & b = componentFactory->bindBehaviour(s,logic,"playerBehaviours");

    //logic.addBehaviour(new PlayerBehaviours);

    //collidable
    body.friction = 0.1;
    body.setMass(3);

    return player;
}
