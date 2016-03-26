#ifndef SIMPLERAY_H
#define SIMPLERAY_H

#include<string>
#include<SFML/Graphics.hpp>


class SimpleRay
{
public:
    SimpleRay();

    std::string originator; // the object that created the ray, this can be null I guess, but it shouldn't be
    std::string target; //if there is a named target, the name goes here. Can happily be empty

    sf::Vector2f startPosition;
    sf::Vector2f targetPosition; //is the desired end position, not the cutoff point
    sf::Vector2f endPosition;

    std::vector<std::string> objectsInContact; //objects the ray is touching
    std::vector<int> collidablesInContact;

};

#endif // SIMPLERAY_H
