#ifndef GAMEOBJECTSTACK_H
#define GAMEOBJECTSTACK_H

#include <gameobject.h>
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

    GameObject* addObject();
    GameObject* addObject(std::string);

    std::map<std::string,GameObject> objects;

private:

    GameObject* generateObject(std::string);

    std::string placeholder;
    int currentId;

};
}
#endif // GAMEOBJECTSTACK_H
