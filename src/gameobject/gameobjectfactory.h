#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <gameobject.h>
#include <gameobjectstack.h>
#include <debugutils.h>

#include <iostream>
#include <vector>
#include<functional>
#include<memory>
#include <map>

namespace BQ{
class GameObjectFactory
{
public:

    GameObjectFactory();
    void setStack(GameObjectStack*);

    DebugUtils* debug;

    //ridiculous number of add functions go here, need some way to generate archetypes for items from file

    void newObject();

    void setDebug(DebugUtils *value);

private:

    GameObjectStack * gameObjects;

};
}

#endif // GAMEOBJECTFACTORY_H
