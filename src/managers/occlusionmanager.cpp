#include "occlusionmanager.h"

#include <game.h>

using namespace BQ;
typedef std::map<std::string, int>::iterator it;


OcclusionManager::OcclusionManager()
{

}

std::vector<int> OcclusionManager::getActiveComponents(std::string tag)
{
    std::vector<int> components;
    for(unsigned int i=0; i<activeObjects.size();i++)
    {
        GameObject & o = gameObjectLoader->loadGameObject(activeObjects[i]);
        std::map<std::string,int> m = o.components[tag];
        std::vector<int> thisComponents(0);
        for(it iterator = m.begin(); iterator != m.end(); iterator++) {

            thisComponents.push_back(iterator->second);
        }

        components.insert(components.end(), thisComponents.begin(), thisComponents.end());
    }
    return components;
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

