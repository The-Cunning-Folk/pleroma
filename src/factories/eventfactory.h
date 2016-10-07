#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include<factory.h>
#include<eventengine.h>
#include<physicalexchange.h>

namespace BQ{
class Game;
class EventFactory : public Factory
{
public:
    EventFactory();

    EventEngine* eventEngine;
    Game* game;

    void createEvent(std::string,std::string);
    void createEvent(std::string,GameObject&);
    void createCollision(Collision);
    void createPhysicsExchange(PhysicalExchange);

    EventEngine *getEventEngine() const;
    void setEventEngine(EventEngine *value);

    Game *getGame() const;
    void setGame(Game *value);
};
}

#endif // EVENTFACTORY_H
