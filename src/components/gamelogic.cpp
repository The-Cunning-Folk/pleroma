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

void GameLogic::addBehaviour(int logic)
{
    behaviours.push_back(logic);
}

void GameLogic::addScriptBehaviour(ScriptBehaviour s)
{
    scripts.push_back(s);
}

void GameLogic::addEvent(std::string script, std::string triggered,std::map<std::string,std::string> parsed,ComponentLoader & c)
{
    Event event(script,triggered);
    event.parsedScript = parsed;
    events.push_back(event);
    for(unsigned int i = 0; i<behaviours.size(); i++)
    {
        c.getBehaviour(behaviours[i]).addEvent(event);
    }
}

void GameLogic::collisionWith(GameObject & o, const Collidable & a, const Collidable & b)
{
    //todo: make collisions trigger events
}

void GameLogic::setDelta(float delta)
{

}

void GameLogic::update()
{

}

void GameLogic::wake()
{

}

