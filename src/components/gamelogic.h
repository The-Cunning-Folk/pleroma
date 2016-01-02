#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <component.h>
#include <collidable.h>
#include <behaviour.h>

namespace BQ{

class GameLogic : public Component
{
public:
    GameLogic();

    void addBehaviour(std::shared_ptr<Behaviour>);

    void addEvent(std::string,std::string,std::map<std::string,std::string>);

    void collisionWith(GameObject&,const Collidable &,const Collidable&);

    void setDelta(float);

    void update();

     std::vector<std::shared_ptr<Behaviour>> behaviours;

private:


};
}

#endif // GAMELOGIC_H
