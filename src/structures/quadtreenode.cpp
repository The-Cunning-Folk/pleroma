#include "quadtreenode.h"

using namespace BQ;

QuadtreeNode::QuadtreeNode()
{
    nodes.resize(0);
    objects.resize(0);
}

void QuadtreeNode::addObject(Collidable * c)
{
    objects.push_back(c);
}

void QuadtreeNode::setBounds(sf::FloatRect bounds)
{
    this->bounds = bounds;

}

void QuadtreeNode::split()
{
    nodes.resize(4);
    for(unsigned int i=0; i<2; i++)
    {
        for(unsigned int j=0; j<2; j++)
        {
            sf::FloatRect nodeBounds(bounds.left + (0.5*bounds.width)*i,bounds.top + (0.5*bounds.height)*j,0.5*bounds.width,0.5*bounds.height);
            nodes[i+j*2].setBounds(nodeBounds);
            nodes[i+j*2].level = level+1;
        }
    }
}

void QuadtreeNode::clear()
{
    objects.clear();
    for(int i=0; i<nodes.size();i++)
    {
        nodes[i].clear();
    }
}

void QuadtreeNode::subdivide()
{
    //nodes.resize(4);
    //std::vector<Collidable*> tempObj(0);

    for(unsigned int i=0; i<objects.size(); i++)
    {

        bool tl,tr,bl,br;
        tl = nodes[0].bounds.intersects(objects[i]->bBox);
        bl = nodes[1].bounds.intersects(objects[i]->bBox);
        tr = nodes[2].bounds.intersects(objects[i]->bBox);
        br = nodes[3].bounds.intersects(objects[i]->bBox);

        if(tl && !bl && !tr && !br)
        {
            //I'm in the top left
            nodes[0].addObject(objects[i]);
            objects[i]->quadtreeLevel = level+1;
        }
        else if(!tl && bl && !tr && !br)
        {
            //I'm in the bottom left
            nodes[1].addObject(objects[i]);
            objects[i]->quadtreeLevel = level+1;
        }
        else if(!tl && !bl && tr && !br)
        {
            //I'm in the top right
            nodes[2].addObject(objects[i]);
            objects[i]->quadtreeLevel = level+1;
        }
        else if(!tl && !bl && !tr && br)
        {
            //I'm in the bottom right
            nodes[3].addObject(objects[i]);
            objects[i]->quadtreeLevel = level+1;
        }
        else
        {
            //keep the object in this node
            objects[i]->quadtreeLevel = level;
        }

    }
}

