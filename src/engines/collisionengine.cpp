#include "collisionengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<game.h>

using namespace BQ;

CollisionEngine::CollisionEngine() : Engine()
{
    placeholder = "auto_coll_";
    quadtree.setRegion(sf::FloatRect(0,0,480,270));
    quadtree.initialise();
    rectShape.setOutlineThickness(1.0);
    rectShape.setFillColor(sf::Color::Transparent);
}


Collidable & CollisionEngine::addCollidable()
{
    collidables.resize(collidables.size()+1);
    return collidables.back();
}

bool CollisionEngine::checkCollision(Collidable & a,Collidable & b)
{
    if(a.bBox.intersects(b.bBox))
    {
        //SAT HERE
        if(separatingAxisCheck(a.polygon,b.polygon))
        {
            a.colliding = true;
            b.colliding = true;
            return true;
        }
        else {
            return false;
        }
    }
}

bool CollisionEngine::separatingAxisCheck(ConvexPolygon & a, ConvexPolygon & b)
{
    //first poly
    std::vector<sf::Vector2f> axes;
    if(a.points.size() < 1 || b.points.size() < 1) {return false;}
    for(int i=1; i<a.points.size();i++)
    {
        //get difference
        sf::Vector2f axis = a.points[i] - a.points[i-1];
        //find normal vector
        sf::Vector2f normAxis = maths->unitNormal(axis);
        axes.push_back(normAxis);
    }
    for(int i=1; i<b.points.size();i++)
    {
        //get difference
        sf::Vector2f axis = b.points[i] - b.points[i-1];
        //find normal vector
        sf::Vector2f normAxis = maths->unitNormal(axis);
        axes.push_back(normAxis);
    }
    for(int i=0; i<axes.size(); i++)
    {
        Projection pA = projection(a,axes[i]);
        Projection pB = projection(b,axes[i]);

        if(!pA.overlaps(pB)) {return false;}
    }
    return true;
}

Projection CollisionEngine::projection(ConvexPolygon & shape, sf::Vector2f axis)
{
    float min = maths->dot(shape.position + shape.points[0],axis);
    float max = min;
    for(int i=0; i<shape.points.size(); i++)
    {
        sf::Vector2f p = shape.position + shape.points[i];
        float dot = maths->dot(p,axis);
        if(dot < min)
        {
            min = dot;
        } else if (dot > max)
        {
            max = dot;
        }
    }
    return (Projection(min,max));
}

void CollisionEngine::run()
{

    quadtree.clear();
    ComponentLoader& components = *componentLoader;
    for(unsigned int i=0; i<collidables.size(); i++)
    {
        Transform & t = components.getTransform(collidables[i].getTransform());
        ConvexPolygon& p = collidables[i].polygon;
        p.setPosition(t.getPosition());
        collidables[i].update();
        collidables[i].setBBox(p.bBox);
        quadtree.addObject(&collidables[i]);
    }

    quadtree.build();

    for(unsigned int i=0; i<quadtree.flatNodes.size(); i++)
    {
        QuadtreeNode & node = quadtree.flatNodes[i];
        int indexChecked = 0;
        for(unsigned int j=0; j<node.objects.size();j++)
        {
            int jLevel = node.objects[j]->quadtreeLevel;
            if(node.objects[j]->quadtreeLevel == node.level) //primary nodes only fool
            {
                for(unsigned int k=0; k<node.objects.size();k++)
                {
                    if(k==j){continue;}
                    int kLevel = node.objects[k]->quadtreeLevel;
                    if(kLevel == jLevel && k < indexChecked) {continue;}
                    checkCollision(*node.objects[j],*node.objects[k]);
                }
                indexChecked = j;
            }
        }
    }

}

void CollisionEngine::drawDebug()
{
    if(gameWindow != NULL){
        GameWindow& window = *gameWindow;
        rectShape.setOutlineThickness(1.0);
        for(unsigned int i=0; i<quadtree.flatNodes.size(); i++)
        {
            sf::FloatRect bBox = quadtree.flatNodes[i].bounds;
            rectShape.setOutlineColor(sf::Color::Cyan);
            rectShape.setPosition(bBox.left+1,bBox.top+1);
            rectShape.setSize(sf::Vector2f(bBox.width-2,bBox.height-2));
            window.draw(rectShape);
        }
        rectShape.setOutlineThickness(1.0);
        for(unsigned int i=0; i<collidables.size(); i++)
        {
            sf::FloatRect bBox = collidables[i].getBBox();
            rectShape.setOutlineColor(sf::Color::Red);
            rectShape.setPosition(bBox.left+1,bBox.top+1);
            rectShape.setSize(sf::Vector2f(bBox.width-2,bBox.height-2));
            if(collidables[i].colliding)
            {
                rectShape.setOutlineColor(sf::Color::Green);
            }
            window.draw(rectShape);
        }

        for(unsigned int i=0; i<collidables.size(); i++)
        {
            sf::ConvexShape shape;
            ConvexPolygon& p = collidables[i].polygon;
            shape.setPointCount(p.points.size());
            for(unsigned int j=0; j<p.points.size(); j++)
            {
                shape.setPoint(j,p.points[j]);
            }
            shape.setPosition(p.position);
            shape.setFillColor(sf::Color::White);
            if(collidables[i].colliding)
            {
                shape.setFillColor(sf::Color::Green);
            }
            window.draw(shape);
        }


    }
}

