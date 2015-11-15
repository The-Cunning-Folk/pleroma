#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<component.h>
#include <iostream>
#include <vector>
#include<functional>
#include<memory>
#include <map>


class GameObject
{
public:
    GameObject();

    std::string name;
    int uniqueId;

    void addComponent(Component*);
    Component* getComponentByName(std::string);


private:

    std::map<std::string,Component*> components;
};

#endif // GAMEOBJECT_H
