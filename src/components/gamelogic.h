#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <component.h>
#include <collidable.h>

namespace BQ{

class Behaviour;

typedef std::shared_ptr<Behaviour> logic_ptr;


class GameLogic : public Component
{
public:
    GameLogic();

    void addBehaviour(Behaviour*);

    void addEvent(std::string,GameObject*,std::map<std::string,std::string>);

    void collisionWith(const GameObject&,const Collidable &,const Collidable&);

    void setDelta(float);

    void update();

private:

    std::vector<logic_ptr> behaviours;
};
}

#endif // GAMELOGIC_H
