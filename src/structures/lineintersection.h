#ifndef LINEINTERSECTION_H
#define LINEINTERSECTION_H

#include<SFML/Graphics.hpp>


class LineIntersection
{
public:
    LineIntersection();

    bool intersects;
    sf::Vector2f intersectionPoint;

};

#endif // LINEINTERSECTION_H
