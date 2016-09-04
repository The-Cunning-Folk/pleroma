#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <component.h>
#include <transform.h>

namespace BQ{


class RigidBody : public Component
{
public:
    RigidBody();

    sf::Vector2f momentum;
    float restitution;
    float friction;

    float getMass() const;
    void setMass(float value);
    float getInvmass() const;

    void update();
    void wake();


protected:

    float mass;
    float invmass;
};

}

#endif // RIGIDBODY_H
