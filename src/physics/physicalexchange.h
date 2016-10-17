#ifndef PHYSICALEXCHANGE_H
#define PHYSICALEXCHANGE_H

#include <SFML/Graphics.hpp>
#include <string>

class PhysicalExchange
{
public:
    PhysicalExchange();

    std::string gameObjectA;
    std::string gameObjectB;
    int rigidBodyA;
    int rigidBodyB;
    int collidableA;
    int collidableB;
    sf::Vector2f reflectionAxis;
};

#endif // PHYSICALCOLLISION_H
