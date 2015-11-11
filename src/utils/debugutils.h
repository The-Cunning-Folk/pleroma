#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <iostream>
#include <string>

#include <timeutils.h>

//this class should act as a penknife for debugging,
//so it's possible to get sensible information everywhere

namespace BQ{

class DebugUtils
{
public:
    DebugUtils();

    TimeUtils time;

    void println(std::string);
    void printerr(std::string);
    void printwarn(std::string);
    void printVal(std::string, std::string);
    void printVal(std::string, float);
    void printVal(std::string, int);
    void printVal(std::string, long);
    void printVal(std::string, double);

private:



};

}

#endif // DEBUGUTILS_H
