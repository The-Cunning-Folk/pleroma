#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<component.h>
#include <iostream>
#include <vector>
#include<functional>
#include<memory>
#include <map>

namespace BQ{
class GameObject
{
public:
    GameObject();

    std::string name;
    int uniqueId;

    void addComponent(Component*);
    void addComponent(std::string,Component*);
    Component* getComponentByName(std::string);

    void update();


private:

    std::map<std::string,Component*> components;
};
}

#endif // GAMEOBJECT_H
