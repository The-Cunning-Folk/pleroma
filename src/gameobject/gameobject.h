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

    Transform* transform;

    std::string name;
    int uniqueId;

    void addComponent(Component*);
    void addComponent(std::string,Component*);
    Component* getComponentByName(std::string);
    std::map<std::string,Component*> getComponentsByType(std::string);

    void update();

    Transform *getTransform() const;
    void setTransform(Transform *value);

    void setPosition(sf::Vector2f);

private:

    std::map<std::string,std::map<std::string,Component*>> components;

};
}

#endif // GAMEOBJECT_H
