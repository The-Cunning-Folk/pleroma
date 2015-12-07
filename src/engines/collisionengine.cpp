#include "collisionengine.h"

#include<eventfactory.h>
#include<componentloader.h>

using namespace BQ;

CollisionEngine::CollisionEngine() : Engine()
{
    placeholder = "auto_coll_";
    quadtree.setRegion(sf::FloatRect(0,0,480,270));
    quadtree.initialise();
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

    quadtree.clear();
    for(unsigned int i=0; i<collidables.size(); i++)
    {
        collidables[i].setBBox(componentLoader->getTransform(collidables[i].getTransform()).getBBox());
        collidables[i].update();
        quadtree.addObject(&collidables[i]);
    }

    quadtree.build();

    for(unsigned int i=0; i<quadtree.flatNodes.size(); i++)
    {
        QuadtreeNode & node = quadtree.flatNodes[i];
        for(unsigned int j=0; j<node.objects.size();j++)
        {
            if(node.objects[j]->quadtreeLevel == node.level) //primary nodes only fool
            {
                for(unsigned int k=0; k<node.objects.size();k++)
                {
                    if(k==j){continue;}
                    checkCollision(*node.objects[j],*node.objects[k]);
                }
            }
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
        gameWindow->draw(quadtree);
    }
}

