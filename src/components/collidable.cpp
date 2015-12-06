#include "collidable.h"

#include <componentloader.h>

using namespace BQ;

Collidable::Collidable()
{
    typeId = "collidable";
    rectShape.setOutlineThickness(1.0);
    rectShape.setFillColor(sf::Color::Transparent);
    rectShape.setOutlineColor(sf::Color::Red);
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
    rectShape.setOutlineColor(color);
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
    rectShape.setOutlineColor(sf::Color::Red);
    rectShape.setPosition(bBox.left,bBox.top);
    rectShape.setSize(sf::Vector2f(bBox.width,bBox.height));
}

Transform & Collidable::loadTransform()
{
    return componentLoader->getTransform(transform);
}

