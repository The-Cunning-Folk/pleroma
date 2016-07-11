#ifndef FLOWPATHINGBEHAVIOURS_H
#define FLOWPATHINGBEHAVIOURS_H

#include<behaviour.h>

namespace BQ{

class FlowPathingBehaviours : public Behaviour
{
public:
    FlowPathingBehaviours();

    float pathSpeed;
    bool active;
    bool path;
    bool hasLOS;
    float targetProximity;
    std::string target;

    void collisionWith(GameObject &, std::string, std::string);

    void beforeEvents();
    void resolveEvent(Event &);
    void update();
};

}

#endif // FLOWPATHINGBEHAVIOURS_H
