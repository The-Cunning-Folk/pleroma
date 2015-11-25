#ifndef EVENT_H
#define EVENT_H

#include<gameobject.h>

namespace BQ{

class Event
{
public:
    Event();

    GameObject* triggeredBy;
    std::string script;

};
}

#endif // EVENT_H
