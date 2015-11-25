#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>
#include<SFML/Graphics.hpp>
#include<mathsutils.h>
#include<debugutils.h>

namespace BQ{
class GameObject;

class Component : public sf::Drawable
{
public:
    Component();

    DebugUtils* debug;

    std::string name; //name of the component. All components should be named
    std::string typeId; //what type of component am I?
    int uniqueId; //a unique component id... not sure how I'll track this but we'll try
    int index;

    void setParent(GameObject*);
    void setName(std::string);

    virtual void update()
    {
        //nothing here
    }


    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);

    GameObject *getParent() const;

private:

    GameObject* parent; //shouldn't always need this, but very useful for some things

};
}

#endif // COMPONENT_H
