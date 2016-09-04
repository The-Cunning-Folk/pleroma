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

    void wake();

    void start();
    void run();
    void finish();

    float grav;

    void addCollision(const PhysicalCollision &);

    std::vector<PhysicalCollision> collisions;

};
}

#endif // PHYSICSENGINE_H
