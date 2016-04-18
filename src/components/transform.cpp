#include "transform.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;

Transform::Transform()
{
    typeId = "transform";
    position.x = position.y = 0;
    position.y = 0;
    size.x = size.y = 10;
    velocity.x = velocity.y = 0;
    correction.x = correction.y = 0;
}

sf::Vector2f Transform::getVelocity() const
{
    return velocity;
}

void Transform::setVelocity(const sf::Vector2f &value)
{
    velocity = value;
}

sf::FloatRect Transform::getBBox()
{
    return sf::FloatRect(position.x-0.5*size.x,position.y-0.5*size.y,size.x,size.y);
}

sf::Vector2f Transform::getSize() const
{
    return size;
}

void Transform::setSize(const sf::Vector2f &value)
{
    size = value;
}

void Transform::setPosition(const sf::Vector2f &value)
{
    position = value;
}


void Transform::update()
{
    step = velocity;
    //set velocity to 0
    velocity = sf::Vector2f(0,0);
}

sf::Vector2i Transform::getWindowPosition() const
{
    return windowPosition;
}

void Transform::setWindowPosition(const sf::Vector2i &value)
{
    windowPosition = value;
}

sf::Vector2f Transform::getPosition() const
{
    return position;
}

sf::Vector2i Transform::getGridPosition() const
{
    return gridPosition;
}

void Transform::setGridPosition(const sf::Vector2i &value)
{
    gridPosition = value;
}

void Transform::move(sf::Vector2f value)
{
    setPosition(position + value);
}

void Transform::move(sf::Vector2i value)
{
    move(sf::Vector2f(value.x,value.y));
}

void Transform::move(float x, float y)
{
    move(sf::Vector2f(x,y));
}

void Transform::move(int x, int y)
{
    move(sf::Vector2f(x,y));
}

