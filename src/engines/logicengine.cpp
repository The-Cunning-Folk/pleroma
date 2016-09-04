#include "logicengine.h"

#include<game.h>


using namespace BQ;

void LogicEngine::wake()
{

}

Behaviour &LogicEngine::bindBehaviour(GameLogic & g, std::string type)
{
    logicUnit newBehaviour = logicUnit(new Behaviour);
    //specific behavioural injection here!

    if(type == "playerBehaviours")
    {
        newBehaviour.reset(new PlayerBehaviours);
    }
    if(type == "flowPathingBehaviours")
    {
        newBehaviour.reset(new FlowPathingBehaviours);
    }

    newBehaviour->parent = g.getParent();
    newBehaviour->setGame(game);
    newBehaviour->index = behaviours.size();

    behaviours.push_back(std::move(newBehaviour));

    g.addBehaviour(behaviours.back()->index);

    Behaviour & b = *behaviours.back();

    return b;
}

Behaviour &LogicEngine::getBehaviour(int index)
{
    return *behaviours[index];
}

LogicEngine::LogicEngine()
{

}

