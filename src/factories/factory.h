#ifndef FACTORY_H
#define FACTORY_H

#include <debugutils.h>
#include <mathsutils.h>

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

    MathsUtils* maths;

    void setDebug(DebugUtils *value);

    void setMaths(MathsUtils *value);
};

}

#endif // FACTORY_H
