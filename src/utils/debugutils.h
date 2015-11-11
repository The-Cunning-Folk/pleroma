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

private:



};

}

#endif // DEBUGUTILS_H
