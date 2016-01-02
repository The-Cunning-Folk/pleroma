#ifndef PHYSICALCOLLISION_H
#define PHYSICALCOLLISION_H

#include <SFML/Graphics.hpp>
#include <string>

class PhysicalCollision
{
public:
    PhysicalCollision();

    std::string gameObjectA;
    std::string gameObjectB;
    int rigidBodyA;
    int rigidBodyB;
    int collidableA;
    int collidableB;

    sf::Vector2f overlap;
};

#endif // PHYSICALCOLLISION_H
