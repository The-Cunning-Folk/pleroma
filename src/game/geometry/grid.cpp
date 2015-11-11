#include "grid.h"

using namespace BQ;

Grid::Grid()
{
    setOrigin(0,0);
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

    debug->printVal("grid scale",scale);
    debug->printVal("grid power",power);
}

sf::Vector2f Grid::getOrigin() const
{
    return origin;
}

void Grid::setOrigin(const sf::Vector2f &value)
{
    origin = value;
}

void BQ::Grid::setOrigin(float x, float y)
{
    sf::Vector2f newOrigin(x,y);
    setOrigin(newOrigin);
}

sf::Vector2i BQ::Grid::getGridPosition(sf::Vector2f position)
{
    int x = (int) ceil(position.x);
    int y = (int) ceil(position.y);

    int gridx = x<<power;
    int gridy = y<<power;

    sf::Vector2i gridPosition(gridx,gridy);

    return(gridPosition);
}

sf::Vector2i Grid::getGridPosition(float x, float y)
{
    sf::Vector2f position(x,y);
    return getGridPosition(position);
}

sf::Vector2f BQ::Grid::getCentre(sf::Vector2i gridPosition)
{

}

void Grid::setDebug(DebugUtils *value)
{
    debug = value;
}
