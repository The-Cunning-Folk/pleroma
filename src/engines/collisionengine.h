#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include <engine.h>
#include <collidable.h>

namespace BQ{
class CollisionEngine : public Engine
{
public:
    CollisionEngine();

    Collidable* addCollidable();

    bool checkCollision(Collidable &,Collidable &);

    void run();
    void drawDebug();

protected:

    std::vector<Collidable> collidables;
};
}

#endif // COLLISIONENGINE_H
