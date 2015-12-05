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

bool CollisionEngine::checkCollision(Collidable & a,Collidable & b)
{
    if(a.bBox.intersects(b.bBox))
    {
        a.setBBoxRectColor(sf::Color::Cyan);
        b.setBBoxRectColor(sf::Color::Cyan);
        return true;
    }
}

void CollisionEngine::run()
{
    for(unsigned int i=0; i<collidables.size(); i++)
    {
        collidables[i].update();
    }
    for(unsigned int i=0; i<collidables.size(); i++)
    {
        for(unsigned int j=i+1; j<collidables.size(); j++)
        {
            checkCollision(collidables[i],collidables[j]);
        }
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

