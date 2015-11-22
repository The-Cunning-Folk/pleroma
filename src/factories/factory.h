#ifndef FACTORY_H
#define FACTORY_H

#include <debugutils.h>

namespace BQ {

class Factory
{
public:
    Factory();

    DebugUtils* debug;

     void setDebug(DebugUtils *value);
};

}

#endif // FACTORY_H
