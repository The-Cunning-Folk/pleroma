#include "collisionengine.h"

using namespace BQ;

CollisionEngine::CollisionEngine()
{

}

Collidable *CollisionEngine::addCollidable()
{
    collidables.resize(collidables.size()+1);
    return & collidables.back();
}

void CollisionEngine::run()
{
    for(unsigned int i=0; i<collidables.size(); i++)
    {
        collidables[i].update();
    }
}

void CollisionEngine::drawDebug()
{
    if(gameWindow != NULL){
        for(unsigned int i=0; i<collidables.size(); i++)
        {
            gameWindow->draw(collidables[i]);
        }
    }
}

