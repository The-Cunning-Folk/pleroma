#ifndef PHYSICSEVENTFACTORY_H
#define PHYSICSEVENTFACTORY_H

#include<factory.h>
#include<physicsengine.h>

namespace BQ{
class PhysicsEventFactory : public Factory
{
public:
    PhysicsEventFactory();

    PhysicsEngine* physicsEngine;

    void newCollision(PhysicalCollision);

    PhysicsEngine *getPhysicsEngine() const;
    void setPhysicsEngine(PhysicsEngine *value);
};
}

#endif // PHYSICSEVENTFACTORY_H
