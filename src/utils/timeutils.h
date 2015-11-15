#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <SFML/System.hpp>
#include <map>
#include <memory>
#include <string>


namespace BQ{

class DebugUtils; //forward definition

class TimeUtils
{
public:
    TimeUtils();

    sf::Clock* addClock(std::string);
    sf::Clock* getClock(std::string);
    sf::Time restartClock(std::string);
    sf::Time restartClock();
    sf::Time getTime(std::string);
    sf::Time getTime();
    float getSeconds(std::string);
    float getSeconds();
    float getSecondsAndRestart(std::string);
    float getSecondsAndRestart();


    void injectDebug(BQ::DebugUtils*);

private:

    sf::Clock globalClock;

    BQ::DebugUtils* debug;

    std::map<std::string,sf::Clock> clocks;

};
}

#endif // TIMEUTILS_H
