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
    void setStack(GameObjectStore*);

    //ridiculous number of add functions go here, need some way to generate archetypes for items from file
    ComponentFactory* componentFactory;

    GameObject& newObject();
    GameObject& newObject(std::string);

    GameObject& buildGameObjectFromPattern(GameObjectPattern &);
    GameObject& buildGameObjectFromPattern(GameObjectPattern &, std::string);
    GameObject& buildComponentsFromPattern(GameObjectPattern &, GameObject & g);

    GameObject& newPlayerObject();

    GameObject& newPathingObject();
    GameObject& newPathingObject(std::string);

    GameObject & makePathingObject(GameObject &);
    GameObject & makePlayerSeekingObject(GameObject &);
    GameObject & makeFlockingObject(GameObject &);

    ComponentFactory *getComponentFactory() const;
    void setComponentFactory(ComponentFactory *value);


private:

    GameObjectStore * gameObjects;

};
}

#endif // GAMEOBJECTFACTORY_H
