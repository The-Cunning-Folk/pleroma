#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include<vector>
#include<string>
#include<event.h>

namespace BQ{

class GameObject;

class Behaviour
{
public:
    Behaviour();

    float delta;

    GameObject* parent;

    std::vector<Event> events;

    void addEvent(Event);

    virtual void resolveEvents();

    void clearEvents();

    void update();

    float getDelta() const;
    void setDelta(float value);
};
}

#endif // BEHAVIOUR_H
