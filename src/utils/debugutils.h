#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <iostream>
#include <string>

#include <timeutils.h>
#include <logger.h>
#include <SFML/Graphics.hpp>

//this class should act as a penknife for debugging,
//so it's possible to get sensible information everywhere

namespace BQ{

class DebugUtils
{
public:
    DebugUtils();

    TimeUtils time;

    Logger *warnLog;
    Logger *errorLog;
    Logger *infoLog;

    void println(std::string);
    void printerr(std::string);
    void printwarn(std::string);
    void printinfo(std::string);
    void printVal(float);
    void printVal(int);
    void printVal(unsigned int);
    void printVal(std::string, std::string);
    void printVal(std::string, float);
    void printVal(std::string, int);
    void printVal(std::string, unsigned int);
    void printVal(sf::FloatRect);

private:



};

}

#endif // DEBUGUTILS_H
