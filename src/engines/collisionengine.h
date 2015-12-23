#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include <engine.h>
#include <collidable.h>
#include <quadtree.h>

namespace BQ{
class CollisionEngine : public Engine
{
public:
    CollisionEngine();

    Collidable& addCollidable();

    bool checkCollision(Collidable &,Collidable &);
    bool separatingAxisCheck(ConvexPolygon &, ConvexPolygon &);

    sf::RectangleShape rectShape;

    Quadtree quadtree;

    void run();
    void drawDebug();

protected:

    std::vector<Collidable> collidables;
};
}

#endif // COLLISIONENGINE_H
