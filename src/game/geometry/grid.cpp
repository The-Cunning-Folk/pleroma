#include "grid.h"

using namespace BQ;

Grid::Grid()
{
    setOrigin(0,0); //can't see myself ever wanting this to not be 0,0
    setScale(0);
}


int Grid::getScale() const
{
    return scale;
}

void Grid::setScale(int value)
{
    //must be a power of 2

    if(value <= 0){
        value = 2;
    }
    scale = math.nxtPow2(value);
    power = math.getPow2(scale);
}

sf::Vector2i Grid::getOrigin() const
{
    return origin;
}

void Grid::setOrigin(const sf::Vector2i &value)
{
    origin = value;
}

void BQ::Grid::setOrigin(int x, int y)
{
    sf::Vector2i newOrigin(x,y);
    setOrigin(newOrigin);
}

sf::Vector2i BQ::Grid::getGridPosition(sf::Vector2f position)
{
    int x = (int) ceil(position.x);
    int y = (int) ceil(position.y);

    int gridx = x<<power;
    int gridy = y<<power;

    sf::Vector2i gridPosition(gridx + origin.x,gridy + origin.y);

    return(gridPosition);
}

sf::Vector2i Grid::getGridPosition(float x, float y)
{
    sf::Vector2f position(x,y);
    return getGridPosition(position);
}

sf::Vector2f BQ::Grid::getCentre(sf::Vector2i gridPosition)
{
    float gridPosFx = (float) gridPosition.x;
    float gridPosFy = (float) gridPosition.y;
    float centreX = 0.5*scale*gridPosFx;
    float centreY = 0.5*scale*gridPosFy;
    sf::Vector2f centre(centreX,centreY);
    return(centre);
}

sf::Vector2f Grid::getCentre(int x, int y)
{
    sf::Vector2i pos(x,y);
    return(getCentre(pos));
}

void Grid::setDebug(DebugUtils *value)
{
    debug = value;
}
