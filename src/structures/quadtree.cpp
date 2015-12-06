#include "quadtree.h"

using namespace BQ;

Quadtree::Quadtree()
{

}

sf::FloatRect Quadtree::getRegion() const
{
    return region;
}

void Quadtree::setRegion(const sf::FloatRect &value)
{
    region = value;
    parentNode.bounds = value;
}

void Quadtree::addObject(Collidable * c)
{
    parentNode.addObject(c);
}

void Quadtree::clear()
{
    parentNode.nodes.clear();
    parentNode.objects.clear();
}

void Quadtree::build()
{

}

