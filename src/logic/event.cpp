#include "event.h"

#include <gameobject.h>

using namespace BQ;

Event::Event()
{

}

Event::Event(std::string s, std::string triggerer)
{
    script = s;
    triggeredBy = triggerer;
}

Event::Event(std::string script, GameObject & object)
{
    this->script = script;
    triggeredBy = object.name;
}

