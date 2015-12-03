#include "gamelogic.h"

#include<behaviour.h>

using namespace BQ;

GameLogic::GameLogic()
{
    typeId = "gamelogic";
}

void GameLogic::addBehaviour(Behaviour* logic)
{
    logic->parent = parent;
    behaviours.push_back(std::shared_ptr<Behaviour>(logic));
}

void GameLogic::addEvent(std::string script, GameObject* triggered,std::map<std::string,std::string> parsed)
{
    Event event(script,triggered);
    event.parsedScript = parsed;
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        behaviours[i]->addEvent(event);
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
        behaviours[i]->clearEvents();
    }
}

