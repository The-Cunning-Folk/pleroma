#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>
#include<SFML/Graphics.hpp>
#include<mathsutils.h>
#include<debugutils.h>
#include<grid.h>

namespace BQ{
class GameObject;
class ComponentLoader;
class GameObjectLoader;
class Transform;

class Component
{
public:
    Component();

    std::string name; //name of the component. All components should be named
    std::string typeId; //what type of component am I?
    int uniqueId; //a unique component id... not sure how I'll track this but we'll try
    int index;
    int transform;

    bool active;

    void setName(std::string);

    virtual void update()
    {
        //nothing here
    }
    virtual void wake()
    {
        //nothing here
    }

    void activate();
    void deactivate();

    std::string getParent() const;
    void setParent(const std::string &value);

    int getTransform() const;
    void setTransform(int value);
    Transform & loadTransform();

    std::string parent; //shouldn't always need this, but very useful for some things

protected:

};
}

#endif // COMPONENT_H
