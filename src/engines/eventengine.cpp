#include "eventengine.h"

#include<game.h>

typedef std::map<std::string,std::vector<Event>>::iterator groupIterator;

using namespace BQ;

EventEngine::EventEngine() : Engine()
{
    placeholder = "event_";
}

void EventEngine::start()
{

}

void EventEngine::run()
{
    TimeUtils& time = (debug->time);
    GameObjectStore & os = game->getCurrentLevel().objects;
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
            GameLogic & g = os.gamelogics[index];
            for(unsigned int k = 0; k<g.behaviours.size(); k++)
            {
                componentLoader->getBehaviour(g.behaviours[k]).collisionWith(B,cA.name,cB.name);
            }
            toUpdate.push_back(index);
        }

        for(int j=0; j<logicB.size(); j++)
        {
            int index = logicB[j];
            GameLogic & g = os.gamelogics[index];
            for(unsigned int k = 0; k<g.behaviours.size(); k++)
            {
                componentLoader->getBehaviour(g.behaviours[k]).collisionWith(A,cB.name,cA.name);
            }
            toUpdate.push_back(index);
        }

        std::vector<int> physA = componentLoader->getRigidBodiesFromObject(A);
        std::vector<int> physB = componentLoader->getRigidBodiesFromObject(B);

        if(cA.interactsWithPhysics && cB.interactsWithPhysics)
        {

            PhysicalExchange p;
            p.gameObjectA = c.objectA;
            p.gameObjectB = c.objectB;
            p.collidableA = c.collidableA;
            p.collidableB = c.collidableB;
            p.reflectionAxis = maths->unit(c.overlap);

            if(physA.size()>0 && physB.size() > 0)
            {

                for(int j=0; j<physA.size(); j++)
                {
                    int iA = physA[j];
                    for(int k=0; k<physB.size(); k++)
                    {
                        int iB = physB[k];
                        p.rigidBodyA = iA;
                        p.rigidBodyB = iB;
                        game->eventFactory.createPhysicsExchange(p);
                    }
                }
            }
            else if(physA.size() > 0)
            {
                for(int j=0; j<physA.size(); j++)
                {
                    int iA = physA[j];
                    p.rigidBodyA = iA;
                    game->eventFactory.createPhysicsExchange(p);
                }
            }
            else if(physB.size() > 0)
            {
                for(int j=0; j<physB.size(); j++)
                {
                    int iB = physB[j];
                    p.rigidBodyA = iB;
                    game->eventFactory.createPhysicsExchange(p);
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
                l.addEvent(event.script,event.triggeredBy,event.parsedScript,game->componentLoader);
            }
        }
    }




    delta = time.getSeconds("logicTime");

    for(int i=0; i<activeComponents.size(); i++)
    {
        GameLogic & g = os.gamelogics[activeComponents[i]];
        g.setDelta(delta);
        g.update();

        for(int j=0;j<g.scripts.size();j++)
        {
            sol::table self = game->luaCtrl["Pot"];
            game->luaCtrl["Pot"]["update"](self,g.parent);
        }

        for(int j=0;j<g.behaviours.size();j++)
        {
            Behaviour & b =componentLoader->getBehaviour(g.behaviours[j]);
            b.setDelta(delta);
            b.resolveEvents();
            b.update();
            b.clearEvents();
        }
    }

}

void EventEngine::finish()
{
    events.clear();
    collisions.clear();
    toUpdate.clear();
}

void EventEngine::wake()
{
    GameObjectStore & os = game->getCurrentLevel().objects;
    for(it_gamelogic it = os.gamelogics.begin(); it != os.gamelogics.end(); it++)
    {
        GameLogic & g = it->second;
        g.wake();
    }
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
        l.addEvent(event.script,event.triggeredBy,event.parsedScript,game->componentLoader);
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

void EventEngine::drawDebug()
{
    for (int i=0; i<events.size(); i++)
    {
        debug->println(events[i].script);
    }
}

void EventEngine::load()
{

}

