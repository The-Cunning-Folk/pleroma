#include "collidable.h"

#include <componentloader.h>

using namespace BQ;

Collidable::Collidable()
{
    typeId = "collidable";

}

int Collidable::getTransform() const
{
    return transform;
}

void Collidable::setTransform(int value)
{
    transform = value;
}

void Collidable::setBBoxRectColor(sf::Color color)
{
    //rectShape.setOutlineColor(color);
}

sf::FloatRect Collidable::getBBox() const
{
    return bBox;
}

void Collidable::setBBox(const sf::FloatRect &value)
{
    bBox = value;
}

void Collidable::update()
{
    colliding = false;
    polygon.update();
}

Transform & Collidable::loadTransform()
{
    return componentLoader->getTransform(transform);
}

