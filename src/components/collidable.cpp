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
    physical = true;
    diminutive = false;
    pathable = false;
    opaque = true;

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

    sf::FloatRect lastBox = polygon.bBox;

    polygon.update();

    setBBox(polygon.bBox);

}

void Collidable::wake()
{
    update();
}



