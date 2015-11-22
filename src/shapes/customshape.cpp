#include "customshape.h"

CustomShape::CustomShape()
{

}

sf::Vector2f CustomShape::getPosition() const
{
    return position;
}

void CustomShape::setPosition(const sf::Vector2f &value)
{
    position = value;
}

