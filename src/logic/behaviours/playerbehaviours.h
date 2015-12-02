#ifndef PLAYERBEHAVIOURS_H
#define PLAYERBEHAVIOURS_H

#include<behaviour.h>

namespace BQ{
class PlayerBehaviours : public Behaviour
{
public:
    PlayerBehaviours();

    void resolveEvents();
};
}

#endif // PLAYERBEHAVIOURS_H
