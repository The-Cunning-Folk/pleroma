#include "collisionengine.h"

#include<eventfactory.h>
#include<componentloader.h>

using namespace BQ;

CollisionEngine::CollisionEngine() : Engine()
{
    placeholder = "auto_coll_";
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
    quadtree.setRegion(sf::FloatRect(0,0,480,270));
    quadtree.clear();
    for(unsigned int i=0; i<collidables.size(); i++)
    {
        collidables[i].setBBox(componentLoader->getTransform(collidables[i].getTransform()).getBBox());
        collidables[i].update();
        quadtree.addObject(&collidables[i]);
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

