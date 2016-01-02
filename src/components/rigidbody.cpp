#include "rigidbody.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;

RigidBody::RigidBody()
{
    typeId = "rigidbody";
    setMass(1);
    restitution = 0;
    friction = 0;
}

int RigidBody::getTransform() const
{
    return transform;
}

void RigidBody::setTransform(int value)
{
    transform = value;
}

float RigidBody::getInvmass() const
{
    return invmass;
}

Transform &RigidBody::loadTransform()
{
    return componentLoader->getTransform(transform);
}

void RigidBody::update()
{

}

float RigidBody::getMass() const
{
    return mass;
}

void RigidBody::setMass(float value)
{
    mass = value;
    invmass = 1.0/value;
}

