#include "engine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<game.h>

using namespace BQ;

Engine::Engine()
{
    placeholder = "auto_generic_";
    currentId = 0;
}

MathsUtils *Engine::getMaths() const
{
    return maths;
}

void Engine::setMaths(MathsUtils *value)
{
    maths = value;
}

float Engine::getDelta() const
{
    return delta;
}

void Engine::setDelta(float value)
{
    delta = value;
}

void Engine::setGame(Game *value)
{
    game = value;
}

Game *Engine::getGame() const
{
    return game;
}

ComponentLoader *Engine::getComponentLoader() const
{
    return componentLoader;
}

void Engine::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
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

