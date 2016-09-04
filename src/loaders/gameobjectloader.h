#ifndef GAMEOBJECTLOADER_H
#define GAMEOBJECTLOADER_H

#include <gameobject.h>
#include <gameobjectstore.h>

namespace BQ {
class GameObjectLoader
{
public:
    GameObjectLoader();

    GameObjectStore * gameObjects;

    GameObjectStore *getGameObjects() const;
    void setGameObjects(GameObjectStore *value);

    GameObject & loadGameObject(std::string);
};
}

#endif // GAMEOBJECTLOADER_H
