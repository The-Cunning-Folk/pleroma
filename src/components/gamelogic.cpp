#include "gamelogic.h"

#include<behaviour.h>
#include<playerbehaviours.h>

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;

GameLogic::GameLogic()
{
    typeId = "gamelogic";
}

void GameLogic::addBehaviour(std::shared_ptr<Behaviour> logic)
{
    behaviours.push_back(std::move(std::shared_ptr<Behaviour>(new PlayerBehaviours)));
    behaviours.back()->parent = parent;
    behaviours.back()->setComponentLoader(componentLoader);
    behaviours.back()->setGameObjectLoader(gameObjectLoader);
    behaviours.back()->setMaths(maths);
    behaviours.back()->setDebug(debug);
}

void GameLogic::addEvent(std::string script, std::string triggered,std::map<std::string,std::string> parsed)
{
    Event event(script,triggered);
    event.parsedScript = parsed;
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        behaviours[i]->addEvent(event);
    }
}

void GameLogic::collisionWith(GameObject & o, const Collidable & a, const Collidable & b)
{
    //todo: make collisions trigger events
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        behaviours[i]->collisionWith(o,a.name,b.name);
    }
}

void GameLogic::setDelta(float delta)
{
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        behaviours[i]->setDelta(delta);
    }
}

void GameLogic::update()
{
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        behaviours[i]->resolveEvents();
        behaviours[i]->update();
        behaviours[i]->clearEvents();
    }
}

