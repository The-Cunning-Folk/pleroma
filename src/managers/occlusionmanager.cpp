#include "occlusionmanager.h"

#include <game.h>

using namespace BQ;

OcclusionManager::OcclusionManager()
{

}

std::vector<std::string> OcclusionManager::getActiveObjects() const
{
    return activeObjects;
}

void OcclusionManager::setActiveObjects(const std::vector<std::string> &value)
{
    activeObjects = value;
}

std::vector<std::string> OcclusionManager::getDrawObjects() const
{
    return drawObjects;
}

void OcclusionManager::setDrawObjects(const std::vector<std::string> &value)
{
    drawObjects = value;
}

GameObjectLoader *OcclusionManager::getGameObjectLoader() const
{
    return gameObjectLoader;
}

void OcclusionManager::setGameObjectLoader(GameObjectLoader *value)
{
    gameObjectLoader = value;
}

ComponentLoader *OcclusionManager::getComponentLoader() const
{
    return componentLoader;
}

void OcclusionManager::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

Game *OcclusionManager::getGame() const
{
    return game;
}

void OcclusionManager::setGame(Game *value)
{
    game = value;
}

