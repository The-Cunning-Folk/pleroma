#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <engine.h>
#include <rigidbody.h>
#include <physicalcollision.h>

namespace BQ{
class PhysicsEngine : public Engine
{
public:
    PhysicsEngine();

    void run();

    float grav;

    std::vector<RigidBody> rigidbodies;

    void addCollision(const PhysicalCollision &);

    std::vector<PhysicalCollision> collisions;

    RigidBody & addRigidBody();
    RigidBody & getRigidBody(int);
};
}

#endif // PHYSICSENGINE_H
