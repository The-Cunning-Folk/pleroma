#include "collidable.h"

Collidable::Collidable()
{
    typeId = "collidable";
}

Transform *Collidable::getTransform() const
{
    return transform;
}

void Collidable::setTransform(Transform *value)
{
    transform = value;
}

sf::Rect Collidable::getBBox() const
{
    return bBox;
}

void Collidable::setBBox(const sf::Rect &value)
{
    bBox = value;
}

