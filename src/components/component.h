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

class Component
{
public:
    Component();

    MathsUtils* maths;
    DebugUtils* debug;
    ComponentLoader* componentLoader;
    GameObjectLoader* gameObjectLoader;
    Grid* grid;

    std::string name; //name of the component. All components should be named
    std::string typeId; //what type of component am I?
    int uniqueId; //a unique component id... not sure how I'll track this but we'll try
    int index;

    void setName(std::string);

    virtual void update()
    {
        //nothing here
    }


    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);


    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

    std::string getParent() const;
    void setParent(const std::string &value);

    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);

    MathsUtils *getMaths() const;
    void setMaths(MathsUtils *value);

    Grid *getGrid() const;
    void setGrid(Grid *value);

protected:

    std::string parent; //shouldn't always need this, but very useful for some things

};
}

#endif // COMPONENT_H
