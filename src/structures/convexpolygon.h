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

    sf::FloatRect bBox;

    void addPoint(sf::Vector2f);
    void addPoint(float,float);
    void clearPoints();

    void update();

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &value);
    std::vector<sf::Vector2f> getPoints() const;
    void setPoints(const std::vector<sf::Vector2f> &value);
};

}

#endif // CONVEXPOLYGON_H
