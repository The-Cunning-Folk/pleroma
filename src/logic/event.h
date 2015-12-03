#ifndef EVENT_H
#define EVENT_H

#include<string>
#include<gameobject.h>

namespace BQ{

class Event
{
public:
    Event();
    Event(std::string,GameObject*);

    GameObject* triggeredBy;
    std::string script;
    std::map<std::string,std::string> parsedScript;

};
}

#endif // EVENT_H
