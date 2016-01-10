#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include<vector>
#include<string>
#include<event.h>
#include<mathsutils.h>
#include<debugutils.h>


namespace BQ{

class GameObject;
class GameObjectLoader;
class ComponentLoader;

class Behaviour
{
public:
    Behaviour();

    ComponentLoader* componentLoader;
    GameObjectLoader* gameObjectLoader;
    MathsUtils* maths;
    DebugUtils* debug;


    float delta;

    std::string parent;

    std::vector<Event> events;

    void addEvent(Event);

    virtual void resolveEvents();

    void clearEvents();

    virtual void update();
    virtual void collisionWith(GameObject &, std::string, std::string);

    bool compare(std::string,std::string);

    float getDelta() const;
    void setDelta(float value);
    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);
    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);
    MathsUtils *getMaths() const;
    void setMaths(MathsUtils *value);
    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);
};
}

#endif // BEHAVIOUR_H
