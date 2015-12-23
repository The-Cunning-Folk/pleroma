#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include <engine.h>
#include <collidable.h>
#include <quadtree.h>
#include <projection.h>

namespace BQ{
class CollisionEngine : public Engine
{
public:
    CollisionEngine();

    Collidable& addCollidable();

    bool checkCollision(Collidable &,Collidable &);
    bool separatingAxisCheck(ConvexPolygon &, ConvexPolygon &);
    Projection projection(ConvexPolygon &, sf::Vector2f);

    sf::RectangleShape rectShape;

    Quadtree quadtree;

    void run();
    void drawDebug();

protected:

    std::vector<Collidable> collidables;
};
}

#endif // COLLISIONENGINE_H
