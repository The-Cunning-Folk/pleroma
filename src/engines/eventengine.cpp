#include "eventengine.h"

#include<eventfactory.h>

using namespace BQ;

EventEngine::EventEngine()
{

}

void EventEngine::run()
{
    for(int i=0; i<events.size();i++)
    {
        resolve(events[i]);
    }
    events.clear();
}

void EventEngine::pushEvent(Event event)
{
    events.push_back(event);

}

std::map<std::string,std::string> EventEngine::parseEvent(std::string event)
{
    int openSq = event.find("[");
    int closeSq = event.find("]");

    std::string type = event.substr(0,openSq);
    std::string script = event.substr(openSq+1,closeSq-openSq-1);

    int openBr = script.find("(");
    int closeBr = script.find(")");

    std::string action = script;
    std::string val = "";
    if(openBr > -1 && closeBr > -1){
        action = script.substr(0,openBr);
        val = script.substr(openBr+1,closeBr-openBr-1);
    }

    std::map<std::string,std::string> parsed;

    parsed["type"] = type;
    parsed["action"] = action;
    parsed["val"] = val;
    return parsed;
}

void EventEngine::resolveGlobally(std::string script)
{

}

void EventEngine::resolveLocally(Event& event)
{
    //just temporary code until I can get this working, should be handled with polymorphic behaviour components
    float speed = delta*200.0;
    std::map<std::string,std::string> parsed = parseEvent(event.script);
    if(parsed["action"].compare("X")==0)
    {
        float deltaX = std::stof(parsed["val"])*0.01;
        event.triggeredBy->getTransform()->move(speed*deltaX,0.0);
    }
    if(parsed["action"].compare("Y")==0)
    {
        float deltaY = std::stof(parsed["val"])*0.01;
        event.triggeredBy->getTransform()->move(0.0,speed*deltaY);
    }
    if(event.script.compare("key_input[move_right]")==0)
    {
        event.triggeredBy->getTransform()->move(speed,0.0);
    }
    if(event.script.compare("key_input[move_up]")==0)
    {
        event.triggeredBy->getTransform()->move(0.0,-speed);
    }
    if(event.script.compare("key_input[move_left]")==0)
    {
        event.triggeredBy->getTransform()->move(-speed,0.0);
    }
    if(event.script.compare("key_input[move_down]")==0)
    {
        event.triggeredBy->getTransform()->move(0.0,speed);
    }
}

void EventEngine::resolve(Event& event)
{
    resolveGlobally(event.script);
    resolveLocally(event);
}

float EventEngine::getDelta() const
{
    return delta;
}

void EventEngine::setDelta(float value)
{
    delta = value;
}

