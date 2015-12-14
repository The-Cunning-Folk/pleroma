#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <gameobject.h>
#include <gameobjectstack.h>

#include <componentfactory.h>

#include<factory.h>

#include<playerbehaviours.h>

namespace BQ{
class GameObjectFactory : public Factory
{
public:

    GameObjectFactory();
    void setStack(GameObjectStack*);

    MathsUtils* math;

    //ridiculous number of add functions go here, need some way to generate archetypes for items from file

    ComponentFactory* componentFactory;

    GameObject* newObject();
    GameObject* newObject(std::string);

    GameObject* newCollisionObject();

    GameObject* newPlayerObject();

    ComponentFactory *getComponentFactory() const;
    void setComponentFactory(ComponentFactory *value);

    MathsUtils *getMath() const;
    void setMath(MathsUtils *value);

private:

    GameObjectStack * gameObjects;

};
}

#endif // GAMEOBJECTFACTORY_H
