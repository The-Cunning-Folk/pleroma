#ifndef EVENT_H
#define EVENT_H

#include<gameobject.h>

namespace BQ{

class Event
{
public:
    Event();
    Event(std::string,GameObject*);

    GameObject* triggeredBy;
    std::string script;

};
}

#endif // EVENT_H
