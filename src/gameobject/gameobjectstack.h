#ifndef GAMEOBJECTSTACK_H
#define GAMEOBJECTSTACK_H

#include <gameobject.h>
#include <componentloader.h>
#include <iostream>
#include <vector>
#include<functional>
#include<memory>
#include <map>

namespace BQ{
class GameObjectStack
{
public:
    GameObjectStack();

    ComponentLoader* componentLoader;

    GameObject* addObject();
    GameObject* addObject(std::string);

    std::map<std::string,GameObject> objects;


    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

private:

    GameObject* generateObject(std::string);

    std::string placeholder;
    int currentId;

};
}
#endif // GAMEOBJECTSTACK_H
