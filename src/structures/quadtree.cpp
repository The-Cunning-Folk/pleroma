#include "quadtree.h"

using namespace BQ;

Quadtree::Quadtree()
{
    parentNode.level = 0;
    maxLevels = 3;
    maxObjects = 3;
    flatNodes.resize(0);
}

void Quadtree::initialise()
{
    initialiseNode(parentNode);
}

void Quadtree::initialiseNode(QuadtreeNode & node)
{
    node.split();
    if(node.level <= maxLevels)
    {
        for(int i=0; i<node.nodes.size();i++)
        {
            initialiseNode(node.nodes[i]);
        }
    }
}

sf::FloatRect Quadtree::getRegion() const
{
    return region;
}

void Quadtree::setRegion(const sf::FloatRect &value)
{
    region = value;
    parentNode.setBounds(value);
}

void Quadtree::addObject(Collidable * c)
{
    parentNode.addObject(c);
}

void Quadtree::clear()
{
    parentNode.clear();
    flatNodes.clear();
}

void Quadtree::buildNode(QuadtreeNode & node)
{
    if(node.objects.size() >= maxObjects && node.level <= maxLevels)
    {
        node.subdivide();
        for(int i=0; i<node.nodes.size(); i++)
        {
            buildNode(node.nodes[i]);
        }
    }
    flatNodes.push_back(node);
}

void Quadtree::build()
{
    buildNode(parentNode);
}


