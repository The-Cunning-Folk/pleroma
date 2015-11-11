#include "timeutils.h"

#include <debugutils.h>

using namespace BQ;

TimeUtils::TimeUtils()
{

}

void TimeUtils::injectDebug(DebugUtils * newDebug)
{
    debug = newDebug;
}

sf::Clock* TimeUtils::addClock(std::string name)
{

    if(clocks.count(name))
    {
        //clock with this name exists!
        if(debug != NULL){
            debug->println(name + " already exists");
        }
        return &globalClock;
    }

    sf::Clock newClock;
    clocks[name] = newClock;
    return &clocks[name];
}

sf::Clock* TimeUtils::getClock(std::string name)
{
    if(!clocks.count(name))
    {
        //clock with this name exists!
        if(debug != NULL){
            debug->println(name + " does not exist");
        }
        return &globalClock;
    }

    return &clocks[name];
}

sf::Time TimeUtils::restartClock(std::string name)
{
    return getClock(name)->restart();
}

sf::Time TimeUtils::restartClock() //restarts the global clock
{
    return globalClock.restart();
}

sf::Time TimeUtils::getTime(std::string name)
{
    return getClock(name)->getElapsedTime();
}

sf::Time TimeUtils::getTime() //gets the time from the global clock
{
    return globalClock.getElapsedTime();
}

float TimeUtils::getSeconds(std::string name)
{
    return getClock(name)->getElapsedTime().asSeconds();
}

float TimeUtils::getSeconds() //global
{
    return globalClock.getElapsedTime().asSeconds();
}

float TimeUtils::getSecondsAndRestart(std::string name)
{
    return getClock(name)->restart().asSeconds();
}

float TimeUtils::getSecondsAndRestart()
{
    return globalClock.restart().asSeconds();
}

