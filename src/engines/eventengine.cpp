#include "eventengine.h"

#include<game.h>


using namespace BQ;

EventEngine::EventEngine() : Engine()
{
    placeholder = "event_";
}

GameLogic &EventEngine::addGameLogic()
{
    gameLogics.resize(gameLogics.size() + 1);
    return gameLogics.back();
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
    for(int i=0; i<events.size();i++)
    {
        resolve(events[i]);
    }
    delta = time.getSeconds("logicTime");
//    for(unsigned int i=0; i<toUpdate.size();i++)
//    {
//        int j = toUpdate[i];
//        gameLogics[j].setDelta(delta);
//        gameLogics[j].update();
//    }

    for(int i=0; i<gameLogics.size(); i++)
    {
        gameLogics[i].setDelta(delta);
        gameLogics[i].update();
    }
    events.clear();
    collisions.clear();
    toUpdate.clear();
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
    std::vector<int> logicIndices = componentLoader->getGameLogicsFromObject(*(event.triggeredBy));
    for(unsigned int i=0; i<logicIndices.size(); i++){
        int index = logicIndices[i];
        gameLogics[index].addEvent(event.script,event.triggeredBy,event.parsedScript);
        toUpdate.push_back(index);
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

