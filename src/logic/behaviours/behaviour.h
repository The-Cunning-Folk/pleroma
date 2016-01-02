#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include<vector>
#include<string>
#include<event.h>
#include<componentloader.h>
#include<gameobjectloader.h>

namespace BQ{

class GameObject;

class Behaviour
{
public:
    Behaviour();

    ComponentLoader* componentLoader;
    GameObjectLoader* gameObjectLoader;

    float delta;

    std::string parent;

    std::vector<Event> events;

    void addEvent(Event);

    virtual void resolveEvents();

    void clearEvents();

    void update();

    float getDelta() const;
    void setDelta(float value);
    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);
    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);
};
}

#endif // BEHAVIOUR_H
