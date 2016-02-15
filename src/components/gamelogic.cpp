#include "gamelogic.h"

#include<behaviour.h>
#include<playerbehaviours.h>

#include <gameobject.h>
#include <componentloader.h>
#include<memory>
#include <gameobjectloader.h>

using namespace BQ;

GameLogic::GameLogic()
{
    typeId = "gamelogic";
}

void GameLogic::addBehaviour(Behaviour * logic)
{
    logic->parent = parent;
    logic->setComponentLoader(componentLoader);
    logic->setGameObjectLoader(gameObjectLoader);
    logic->setMaths(maths);
    logic->setDebug(debug);
    logic->setGrid(grid);
    behaviours.push_back(logic);

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
    //debug->printVal((int) behaviours.size());
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        behaviours[i]->resolveEvents();
        behaviours[i]->update();
        behaviours[i]->clearEvents();
    }
}

