#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>

namespace BQ{
class GameObject;

class Component
{
public:
    Component();

    std::string name; //name of the component. All components should be named
    std::string typeId; //what type of component am I?
    int uniqueId; //a unique component id... not sure how I'll track this but we'll try

    void setParent(GameObject*);
    void setName(std::string);

private:

    GameObject* parent; //shouldn't always need this, but very useful for some things

};
}

#endif // COMPONENT_H
