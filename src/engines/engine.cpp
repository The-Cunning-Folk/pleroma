#include "engine.h"

#include<eventfactory.h>

using namespace BQ;

Engine::Engine()
{
    placeholder = "auto_generic_";
    currentId = 0;
}

EventFactory *Engine::getEventFactory() const
{
    return eventFactory;
}

void Engine::setEventFactory(EventFactory *value)
{
    eventFactory = value;
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

