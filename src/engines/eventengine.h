#ifndef EVENTENGINE_H
#define EVENTENGINE_H

#include <engine.h>
#include <event.h>

 //this is a global event aggregator and manager for handling triggered events.
//it is where the beast that will eat my beautiful, efficient engine has slouched to be born
namespace BQ {
class EventEngine : public Engine
{
public:
    EventEngine();

    std::vector<Event> events;

    void run();

    void pushEvent(Event);

    void resolveGlobally(std::string); //check for a global script call
    void resolveLocally(Event&); //use the triggeredBy's behaviour component
    void resolve(Event&);

    float getDelta() const;
    void setDelta(float value);

protected:

    float delta; //the time since the last update


};
}

#endif // EVENTENGINE_H
