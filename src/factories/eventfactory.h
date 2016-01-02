#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include<factory.h>
#include<eventengine.h>

namespace BQ{
class EventFactory : public Factory
{
public:
    EventFactory();

    EventEngine* eventEngine;

    void createEvent(std::string,std::string);
    void createEvent(std::string,GameObject&);
    void createCollision(Collision);

    EventEngine *getEventEngine() const;
    void setEventEngine(EventEngine *value);
};
}

#endif // EVENTFACTORY_H
