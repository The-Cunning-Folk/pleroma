#ifndef FLOWPATHINGBEHAVIOURS_H
#define FLOWPATHINGBEHAVIOURS_H

#include<behaviour.h>

namespace BQ{

class FlowPathingBehaviours : public Behaviour
{
public:
    FlowPathingBehaviours();

    float pathSpeed;

    void collisionWith(GameObject &, std::string, std::string);

    void resolveEvents();
    void update();
};

}

#endif // FLOWPATHINGBEHAVIOURS_H
