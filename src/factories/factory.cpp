#include "factory.h"

using namespace BQ;

Factory::Factory()
{

}

void Factory::setMaths(MathsUtils *value)
{
    maths = value;
}

void Factory::setDebug(DebugUtils *value)
{
    debug = value;
}

