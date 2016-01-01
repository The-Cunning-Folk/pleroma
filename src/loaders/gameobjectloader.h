#ifndef GAMEOBJECTLOADER_H
#define GAMEOBJECTLOADER_H

#include <gameobject.h>
#include <gameobjectstack.h>

namespace BQ {
class GameObjectLoader
{
public:
    GameObjectLoader();

    GameObjectStack * gameObjects;

    GameObjectStack *getGameObjects() const;
    void setGameObjects(GameObjectStack *value);

    GameObject & loadGameObject(std::string);
};
}

#endif // GAMEOBJECTLOADER_H
