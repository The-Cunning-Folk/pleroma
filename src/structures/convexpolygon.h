#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include <vector>
#include <SFML/Graphics.hpp>

namespace BQ{

class ConvexPolygon
{
public:
    ConvexPolygon();

    std::vector<sf::Vector2f> points;
    sf::Vector2f position;

    void addPoint(sf::Vector2f);
    void setPosition(sf::Vector2f);
    void clearPoints();
};

}

#endif // CONVEXPOLYGON_H
