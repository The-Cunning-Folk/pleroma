#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <component.h>
#include <transform.h>

namespace BQ{


class RigidBody : public Component
{
public:
    RigidBody();

    int transform;

    sf::Vector2f momentum;
    float restitution;
    float friction;

    float getMass() const;
    void setMass(float value);
    float getInvmass() const;

    Transform & loadTransform();

    void update();
    void wake();

    int getTransform() const;
    void setTransform(int value);

protected:

    float mass;
    float invmass;
};

}

#endif // RIGIDBODY_H
