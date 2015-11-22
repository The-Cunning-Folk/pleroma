#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<component.h>

namespace BQ {

class Transform : public Component
{
public:
    Transform();

    sf::Vector2i position; //this is the actual position of the object to avoid sprite tearing

    sf::Vector2i gridPosition; //the position of the object on the grid

    sf::Vector2f fPosition; //this is the position that we do work on so that we can scale things nicely

    std::vector <Transform*> children; //transforms that are bound to this one

    void move(sf::Vector2f);
    void move(sf::Vector2i);
    void move(float,float);
    void move(int,int);

};

}

#endif // TRANSFORM_H
