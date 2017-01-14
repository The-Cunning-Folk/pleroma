#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <component.h>
#include <collidable.h>
#include <scriptbehaviour.h>
#include <event.h>


namespace BQ{
class Behaviour;
class GameLogic : public Component
{
public:
    GameLogic();

    void addBehaviour(int);
    void addScriptBehaviour(ScriptBehaviour);

    void addEvent(std::string,std::string,std::map<std::string,std::string>,ComponentLoader &);

    void collisionWith(GameObject&,const Collidable &,const Collidable&);

    void setDelta(float);

    void update();
    void wake();

     std::vector<int> behaviours;
     std::vector<ScriptBehaviour> scripts;
     std::vector<Event> events;

private:


};
}

#endif // GAMELOGIC_H
