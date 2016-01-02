#include "physicseventfactory.h"

#include <game.h>

using namespace BQ;

PhysicsEventFactory::PhysicsEventFactory()
{

}

void PhysicsEventFactory::newCollision(PhysicalCollision c)
{
    //debug->println("hoi");
}

PhysicsEngine *PhysicsEventFactory::getPhysicsEngine() const
{
    return physicsEngine;
}

void PhysicsEventFactory::setPhysicsEngine(PhysicsEngine *value)
{
    physicsEngine = value;
}

