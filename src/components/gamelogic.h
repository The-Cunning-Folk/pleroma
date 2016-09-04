#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <component.h>
#include <collidable.h>



namespace BQ{
class Behaviour;
class GameLogic : public Component
{
public:
    GameLogic();

    void addBehaviour(int);

    void addEvent(std::string,std::string,std::map<std::string,std::string>,ComponentLoader &);

    void collisionWith(GameObject&,const Collidable &,const Collidable&);

    void setDelta(float);

    void update();
    void wake();

     std::vector<int> behaviours;

private:


};
}

#endif // GAMELOGIC_H
