#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<transform.h>

#include<component.h>
#include<gamelogic.h>
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

    int transform;

    std::string name;
    int uniqueId;

    void addComponent(Component*);
    void addComponent(std::string,Component*);

    void update();


    void setPosition(sf::Vector2f);

    int getTransform() const;
    void setTransform(int value);

private:

    std::map<std::string,std::map<std::string,int>> components;

};
}

#endif // GAMEOBJECT_H
