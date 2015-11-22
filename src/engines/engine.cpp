#include "engine.h"

using namespace BQ;

Engine::Engine()
{

}

DebugUtils *Engine::getDebug() const
{
    return debug;
}

void Engine::setDebug(DebugUtils *value)
{
    debug = value;
}

