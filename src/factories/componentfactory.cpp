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
    c.interactsWithPhysics = pattern.physical;
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
    s.frame = pattern.frame;
    if(pattern.paused)
    {
        s.animation.pause();
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


void ComponentFactory::buildRayEmitterFromPattern(BQ::RayEmitterPattern & pattern, BQ::RayEmitter & r)
{
    r.name = pattern.name;
    for(int i = 0; i<pattern.targets.size(); i++)
    {
        r.addTarget(pattern.targets[i]);
    }
    for(int i=0; i<pattern.positions.size(); i++)
    {
        r.positions.push_back(pattern.positions[i]);
    }
}

void ComponentFactory::buildGameLogicFromPattern(GameLogicPattern & pattern, GameLogic & g)
{
    g.name = pattern.name;
//    g.scripts = pattern.scripts;

    for(int i=0; i< pattern.scripts.size(); i++)
    {
        ScriptBehaviour s = pattern.scripts[i];
        if(s.table != "")
        {
            std::string ins = game->math.randomString(10);
            sol::table t = game->luaCtrl["copy_table"](game->luaCtrl[s.table]);
            game->luaCtrl.set(ins,t);
            s.instance=ins;
            g.scripts.push_back(s);
        }

    }
}

LogicEngine *ComponentFactory::getLogicEngine() const
{
    return logicEngine;
}

void ComponentFactory::setLogicEngine(LogicEngine *value)
{
    logicEngine = value;
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


BQ::Transform & ComponentFactory::newTransform(GameObjectStore & s)
{
    return s.addTransform();
}

Transform &ComponentFactory::newTransform(GameObjectStore & s, std::string name)
{
    Transform & transform = newTransform(s);
    transform.setName(name);
    return(transform);
}

Transform &ComponentFactory::newChildTransform(GameObjectStore & s,Transform& parent)
{
    Transform & transform = newTransform(s);
    parent.children.push_back(transform.index);
    return(transform);
}

PlayerInput &ComponentFactory::newPlayerInput(GameObjectStore & s)
{
    return s.addPlayerInput();
}

PlayerInput &ComponentFactory::newPlayerInput(GameObjectStore & s, std::string name)
{
    PlayerInput & input = newPlayerInput(s);
    input.setName(name);
    return(input);
}

GameLogic &ComponentFactory::newGameLogic(GameObjectStore & s)
{
    GameLogic& gameLogic = s.addGameLogic();
    return gameLogic;
}

GameLogic &ComponentFactory::newGameLogic(GameObjectStore &s, std::string name)
{
    GameLogic& gameLogic = newGameLogic(s);
    gameLogic.setName(name);
    return(gameLogic);
}

Behaviour &ComponentFactory::bindBehaviour(GameObjectStore & s, GameLogic & g, std::string type)
{
    Behaviour & b = logicEngine->bindBehaviour(g,type);
    b.setGame(game);
    return b;
}

Collidable & ComponentFactory::newCollidable(GameObjectStore & s)
{
    Collidable & c = s.addCollidable();
    return c;
}

Collidable & ComponentFactory::newCollidable(GameObjectStore & s,std::string name)
{
    Collidable & c = newCollidable(s);
    c.name = name;
    return(c);
}

Collidable &ComponentFactory::newCollidable(GameObjectStore & s,std::vector<sf::Vector2f> points)
{
    Collidable & c = newCollidable(s);

    for(int i=0; i<points.size(); i++)
    {
        c.polygon.addPoint(points[i]);
    }
    return c;
}

RigidBody &ComponentFactory::newRigidBody(GameObjectStore & s)
{
    RigidBody & rigidBody = s.addRigidBody();
    return rigidBody;
}

RigidBody &ComponentFactory::newRigidBody(GameObjectStore & s,std::string name)
{
    RigidBody & rigidBody = newRigidBody(s);
    rigidBody.setName(name);
    return rigidBody;
}

RayEmitter &ComponentFactory::newRayEmitter(GameObjectStore & s)
{
    return s.addRayEmitter();
}

RayEmitter &ComponentFactory::newRayEmitter(GameObjectStore & s,std::string name)
{
    RayEmitter & rayEmitter = newRayEmitter(s);
    rayEmitter.setName(name);
    return rayEmitter;
}

SpriteRenderer &ComponentFactory::newSpriteRenderer(GameObjectStore & s)
{
    return s.addSpriteRenderer();
}

SpriteRenderer &ComponentFactory::newSpriteRenderer(GameObjectStore & s,std::string name)
{
    SpriteRenderer & spriteRenderer = newSpriteRenderer(s);
    spriteRenderer.setName(name);
    return spriteRenderer;
}
