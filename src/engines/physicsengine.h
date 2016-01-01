#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <engine.h>
#include <rigidbody.h>

namespace BQ{
class PhysicsEngine : public Engine
{
public:
    PhysicsEngine();

    void run();

    std::vector<RigidBody> rigidbodies;

    RigidBody & addRigidBody();
};
}

#endif // PHYSICSENGINE_H
