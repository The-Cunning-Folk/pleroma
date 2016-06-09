#ifndef EVENTENGINE_H
#define EVENTENGINE_H

#include <engine.h>
#include <event.h>
#include <collision.h>
#include <gamelogic.h>
#include <playerinput.h>

 //this is a global event aggregator and manager for handling triggered events.
//it is where the beast that will eat my beautiful, efficient engine has slouched to be born
namespace BQ {



class EventEngine : public Engine
{
public:
    EventEngine();

    std::vector<Event> events;
    std::vector<Collision> collisions;
    std::vector<int> toUpdate;

    PhysicsEventFactory* physicsEventFactory;

    std::vector<GameLogic> gameLogics;

    GameLogic& addGameLogic();
    GameLogic& getGameLogic(int);

    void start();
    void run();
    void finish();
    void wake();

    void pushEvent(Event);

    std::map<std::string,std::string> parseEvent(std::string);

    void resolveGlobally(Event&); //check for a global script call
    void resolveLocally(Event&); //use the triggeredBy's behaviour component
    void resolve(Event&);

    float getDelta() const;
    void setDelta(float value);


protected:

    float delta; //the time since the last update


};
}

#endif // EVENTENGINE_H
