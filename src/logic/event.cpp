#include "event.h"

using namespace BQ;

Event::Event()
{

}

Event::Event(std::string script, GameObject * object)
{
    this->script = script;
    triggeredBy = object;
}

