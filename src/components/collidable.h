#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <component.h>
#include <transform.h>
#include <convexpolygon.h>

namespace BQ{
class Collidable : public Component
{
public:
    Collidable();

    int quadtreeLevel;

    //sf::RectangleShape rectShape;

    sf::FloatRect bBox;
    sf::FloatRect tBox; //box which encapsulates the entire sphere of influence of the last step

    void setBBoxRectColor(sf::Color);

    sf::FloatRect getBBox() const;
    void setBBox(const sf::FloatRect &value);

    void update();
    void wake();

    bool solid;
    bool immovable;
    bool diminutive;
    bool pathable;
    bool opaque;
    bool interactsWithPhysics;
    bool colliding;

    ConvexPolygon polygon;

    std::vector<int> collidingWith;

    std::vector<sf::Vector2i> gridEdges;
    std::vector<sf::Vector2i> gridInnerArea;


private:

};
}

#endif // COLLIDABLE_H
