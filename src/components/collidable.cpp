#include "collidable.h"

using namespace BQ;

Collidable::Collidable()
{
    typeId = "collidable";
    rectShape.setOutlineThickness(1.0);
    rectShape.setFillColor(sf::Color::Transparent);
    rectShape.setOutlineColor(sf::Color::Red);
}

Transform *Collidable::getTransform() const
{
    return transform;
}

void Collidable::setTransform(Transform *value)
{
    transform = value;
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
    if(transform != NULL)
    {
        //update positions
        bBox = transform->getBBox();
    }
    rectShape.setPosition(bBox.left,bBox.top);
    rectShape.setSize(sf::Vector2f(bBox.width,bBox.height));
}

