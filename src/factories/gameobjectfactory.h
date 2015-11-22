#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <gameobject.h>
#include <gameobjectstack.h>


#include <iostream>
#include <vector>
#include<functional>
#include<memory>
#include <map>

#include <factory.h>

namespace BQ{
class GameObjectFactory : public Factory
{
public:

    GameObjectFactory();
    void setStack(GameObjectStack*);

    //ridiculous number of add functions go here, need some way to generate archetypes for items from file

    void newObject();

private:

    GameObjectStack * gameObjects;

};
}

#endif // GAMEOBJECTFACTORY_H
