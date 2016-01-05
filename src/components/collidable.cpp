#include "collidable.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;

Collidable::Collidable()
{
    typeId = "collidable";
    collidingWith.resize(0);
    solid = true;
    immovable = false;
    momTransfer = true;

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
    collidingWith.resize(0);
    polygon.update();
}

Transform & Collidable::loadTransform()
{
    return componentLoader->getTransform(transform);
}

