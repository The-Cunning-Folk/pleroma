#include "physicsengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<gameobjectloader.h>
#include<game.h>

using namespace BQ;

PhysicsEngine::PhysicsEngine()
{
    placeholder = "auto_phys_";
}

void PhysicsEngine::run()
{

}

RigidBody &PhysicsEngine::addRigidBody()
{
    rigidbodies.resize(rigidbodies.size()+1);
    rigidbodies.back().index = rigidbodies.size()-1;
    return rigidbodies.back();
}
