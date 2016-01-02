#include "factory.h"

#include <game.h>

using namespace BQ;

Factory::Factory()
{

}

Game *Factory::getGame() const
{
    return game;
}

void Factory::setGame(Game *value)
{
    game = value;
    setMaths(&(game->math));
    setDebug(game->debug);
}

void Factory::setMaths(MathsUtils *value)
{
    maths = value;
}

void Factory::setDebug(DebugUtils *value)
{
    debug = value;
}

