#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include<vector>
#include<string>
#include<event.h>
#include<mathsutils.h>
#include<debugutils.h>
#include<grid.h>


namespace BQ{

class GameObject;
class Game;

class Behaviour
{
public:
    Behaviour();

    Game* game;

    int index;

    float delta;

    std::string parent;

    std::vector<Event> events;

    void addEvent(Event);

    void resolveEvents();
    virtual void beforeEvents();
    virtual void resolveEvent(Event &);

    void clearEvents();

    virtual void update();
    virtual void collisionWith(GameObject &, std::string, std::string);

    bool compare(std::string,std::string);

    float getDelta() const;
    void setDelta(float value);

    Game *getGame() const;
    void setGame(Game *value);
};
}

#endif // BEHAVIOUR_H
