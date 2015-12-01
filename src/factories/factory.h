#ifndef FACTORY_H
#define FACTORY_H

#include <debugutils.h>

#include<iostream>
#include<vector>
#include<functional>
#include<memory>
#include<map>

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
