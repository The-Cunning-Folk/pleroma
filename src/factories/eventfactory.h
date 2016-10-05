#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include<factory.h>
#include<eventengine.h>
#include<physicalexchange.h>

namespace BQ{
class EventFactory : public Factory
{
public:
    EventFactory();

    EventEngine* eventEngine;

    void createEvent(std::string,std::string);
    void createEvent(std::string,GameObject&);
    void createCollision(Collision);
    void createPhysicsExchange(PhysicalExchange);

    EventEngine *getEventEngine() const;
    void setEventEngine(EventEngine *value);
};
}

#endif // EVENTFACTORY_H
