#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include <engine.h>
#include <collidable.h>
#include <quadtree.h>
#include <projection.h>
#include <mtv.h>
#include <collision.h>

namespace BQ{
class CollisionEngine : public Engine
{
public:
    CollisionEngine();

    float overlapThreshold;

    Collidable & getCollidable(int);

    Collidable& addCollidable();

    bool checkCollision(Collidable &,Collidable &);
    sf::Vector2f findMovingCollisionCorrection(Collidable &, Collidable &);
    sf::Vector2f separatingAxisCheck(ConvexPolygon &, ConvexPolygon &);
    Projection projection(ConvexPolygon &, sf::Vector2f);

    std::vector<Collision> collisions;

    sf::RectangleShape rectShape;

    Quadtree quadtree;

    void start();
    void run();
    void finish();
    void drawDebug();
    void wake();

protected:

    std::vector<Collidable> collidables;
};
}

#endif // COLLISIONENGINE_H
