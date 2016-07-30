#ifndef RIGIDBODYPATTERN_H
#define RIGIDBODYPATTERN_H

#include <factorypattern.h>

namespace BQ
{

class RigidBodyPattern : public FactoryPattern
{
public:
    RigidBodyPattern();

    float mass;
    sf::Vector2f momentum;
    float restitution;
    float friction;

    void parse(const rapidjson::Value &);

};
}

#endif // RIGIDBODYPATTERN_H
