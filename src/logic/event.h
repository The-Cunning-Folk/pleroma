#ifndef EVENT_H
#define EVENT_H

#include<string>
#include<memory.h>
#include<map>

namespace BQ{

class Event
{
public:
    Event();
    Event(std::string,std::string);

    std::string triggeredBy;
    std::string script;
    std::map<std::string,std::string> parsedScript;

};
}

#endif // EVENT_H
