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

window_ptr Engine::getGameWindow() const
{
    return gameWindow;
}

void Engine::setGameWindow(const window_ptr &value)
{
    gameWindow = value;
}

