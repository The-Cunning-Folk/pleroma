#include "eventengine.h"

#include<game.h>

typedef std::map<std::string,std::vector<Event>>::iterator groupIterator;

using namespace BQ;

EventEngine::EventEngine() : Engine()
{
    placeholder = "event_";
    gameLogics.resize(0);
}

GameLogic &EventEngine::addGameLogic()
{
    gameLogics.resize(gameLogics.size() + 1);
    gameLogics.back().index = gameLogics.size()-1;
    return gameLogics.back();
}

GameLogic &EventEngine::getGameLogic(int index)
{
    return gameLogics[index];
}

void EventEngine::start()
{

}

void EventEngine::run()
{
    TimeUtils& time = (debug->time);
    for(int i=0; i<collisions.size(); i++)
    {
        //collision logic here
        Collision & c = collisions[i];
        GameObject & A = gameObjectLoader->loadGameObject(c.objectA);
        GameObject & B = gameObjectLoader->loadGameObject(c.objectB);

        Collidable & cA = componentLoader->getCollidable(c.collidableA);
        Collidable & cB = componentLoader->getCollidable(c.collidableB);

        //check for components and do behaviours
        std::vector<int> logicA = componentLoader->getGameLogicsFromObject(A);
        std::vector<int> logicB = componentLoader->getGameLogicsFromObject(B);

        for(int j=0; j<logicA.size(); j++)
        {
            int index = logicA[j];
            gameLogics[index].collisionWith(B,cA,cB);
            toUpdate.push_back(index);
        }

        for(int j=0; j<logicB.size(); j++)
        {
            int index = logicB[j];
            gameLogics[index].collisionWith(A,cB,cA);
            toUpdate.push_back(index);
        }

        std::vector<int> physA = componentLoader->getRigidBodiesFromObject(A);
        std::vector<int> physB = componentLoader->getRigidBodiesFromObject(B);

        if(cA.physical && cB.physical)
        {
            for(int j=0; j<physA.size(); j++)
            {
                int iA = physA[j];
                for(int k=0; k<physB.size(); k++)
                {

                    int iB = physB[k];
                    PhysicalCollision p;
                    p.gameObjectA = c.objectA;
                    p.gameObjectB = c.objectB;
                    p.collidableA = c.collidableA;
                    p.collidableB = c.collidableB;
                    p.rigidBodyA = iA;
                    p.rigidBodyB = iB;
                    p.overlap = c.overlap;
                    game->physicsEventFactory.newCollision(p);

                }
            }
        }

    }

    std::map<std::string,std::vector<Event>> groupedEvents;

    for(int i=0; i<events.size();i++)
    {
        Event & e = events[i];
        resolve(events[i]);
        //group by triggeredByObject
        groupedEvents[e.triggeredBy].push_back(events[i]);

    }


    for(groupIterator iterator = groupedEvents.begin(); iterator != groupedEvents.end(); iterator++) {
        // iterator->first = key
        // iterator->second = value
        // Repeat if you also want to iterate through the second map.

        std::vector<Event> groupedEvents = iterator->second;
        std::string triggeredBy = iterator->first;
        GameObject & g = game->gameObjectLoader.loadGameObject(triggeredBy);
        std::vector<int> logicIndices = game->componentLoader.getGameLogicsFromObject(g);
        for(unsigned int j=0; j<logicIndices.size(); j++)
        {
            int index = logicIndices[j];
            GameLogic & l = game->componentLoader.getGameLogic(index);
            for(int i=0 ; i<groupedEvents.size(); i++)
            {
                Event & event = groupedEvents[i];
                l.addEvent(event.script,event.triggeredBy,event.parsedScript);
            }
        }
    }




    delta = time.getSeconds("logicTime");
//    for(unsigned int i=0; i<toUpdate.size();i++)
//    {
//        int j = toUpdate[i];
//        gameLogics[j].setDelta(delta);
//        gameLogics[j].update();
//    }

    //debug->printVal((int) gameLogics.size());

    for(int i=0; i<activeComponents.size(); i++)
    {
        GameLogic & g = gameLogics[activeComponents[i]];
        g.setDelta(delta);
        g.update();
    }
    events.clear();
    collisions.clear();
    toUpdate.clear();
}

void EventEngine::finish()
{

}

void EventEngine::pushEvent(Event event)
{
    events.push_back(event);

}

std::map<std::string,std::string> EventEngine::parseEvent(std::string event)
{
    int openSq = event.find("{");
    int closeSq = event.find("}");

    std::string type = event.substr(0,openSq);
    std::string script = event.substr(openSq+1,closeSq-openSq-1);

    int openBr = script.find("(");
    int closeBr = script.find(")");

    std::string action = script;
    std::string val = "";
    if(openBr > -1 && closeBr > -1){
        action = script.substr(0,openBr);
        val = script.substr(openBr+1,closeBr-openBr-1);
    }

    std::map<std::string,std::string> parsed;

    parsed["type"] = type;
    parsed["action"] = action;
    parsed["val"] = val;
    return parsed;
}

void EventEngine::resolveGlobally(Event& event)
{
    event.parsedScript = parseEvent(event.script);
}

void EventEngine::resolveLocally(Event& event)
{
    GameObject & g = game->gameObjectLoader.loadGameObject(event.triggeredBy);
    std::vector<int> logicIndices = game->componentLoader.getGameLogicsFromObject(g);
    for(unsigned int i=0; i<logicIndices.size(); i++)
    {
        int index = logicIndices[i];
        GameLogic & l = game->componentLoader.getGameLogic(index);
        l.addEvent(event.script,event.triggeredBy,event.parsedScript);
    }
}

void EventEngine::resolve(Event& event)
{
    resolveGlobally(event);
    resolveLocally(event);
}

float EventEngine::getDelta() const
{
    return delta;
}

void EventEngine::setDelta(float value)
{
    delta = value;
}

