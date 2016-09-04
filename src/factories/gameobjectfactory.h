#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <gameobject.h>
#include <gameobjectstore.h>

#include <componentfactory.h>
#include <gameobjectpattern.h>

#include<factory.h>

#include<playerbehaviours.h>
#include<flowpathingbehaviours.h>

namespace BQ{
class GameObjectFactory : public Factory
{
public:

    GameObjectFactory();
    //ridiculous number of add functions go here, need some way to generate archetypes for items from file
    ComponentFactory* componentFactory;

    GameObject& newObject(GameObjectStore &);
    GameObject& newObject(GameObjectStore &, std::string);

    GameObject& buildGameObjectFromPattern(GameObjectStore &, GameObjectPattern &);
    GameObject& buildGameObjectFromPattern(GameObjectStore &,GameObjectPattern &, std::string);
    GameObject& buildComponentsFromPattern(GameObjectStore &,GameObjectPattern &, GameObject & g);

    GameObject& newPlayerObject();

    ComponentFactory *getComponentFactory() const;
    void setComponentFactory(ComponentFactory *value);


private:

    GameObjectStore * gameObjects;

};
}

#endif // GAMEOBJECTFACTORY_H
