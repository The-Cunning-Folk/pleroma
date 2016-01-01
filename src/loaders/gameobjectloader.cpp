#include "gameobjectloader.h"

using namespace BQ;
GameObjectLoader::GameObjectLoader()
{

}


GameObjectStack *GameObjectLoader::getGameObjects() const
{
    return gameObjects;
}

void GameObjectLoader::setGameObjects(GameObjectStack *value)
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
