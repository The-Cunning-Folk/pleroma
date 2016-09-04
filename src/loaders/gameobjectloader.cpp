#include "gameobjectloader.h"

using namespace BQ;
GameObjectLoader::GameObjectLoader()
{

}


GameObjectStore *GameObjectLoader::getGameObjects() const
{
    return gameObjects;
}

void GameObjectLoader::setGameObjects(GameObjectStore *value)
{
    gameObjects = value;
}

BQ::GameObject &BQ::GameObjectLoader::loadGameObject(std::string name)
{
    if (gameObjects != NULL)
    {
        return gameObjects->objects[name];
    }
}
