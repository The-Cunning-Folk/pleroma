#include "grid.h"

using namespace BQ;

Grid::Grid()
{
    setOrigin(0,0); //can't see myself ever wanting this to not be 0,0
    setScale(16);
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
    debug->println(std::to_string(value));
    if(value%2 != 0){
        scale = math.nxtPow2(value);
    }
    else{
        scale = value;
    }
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

std::vector<sf::Vector2i> Grid::bresenhamLine(sf::Vector2f, sf::Vector2f)
{
    std::vector<sf::Vector2i> squares(0);
    //add bresenham here
    return squares;
}

std::vector<GridSquare> Grid::getActiveSquares() const
{
    return activeSquares;
}

void Grid::setActiveSquares(const std::vector<GridSquare> &value)
{
    activeSquares = value;
}

sf::Vector2i BQ::Grid::getGridPosition(sf::Vector2f position)
{
    int x = (int) ceil(position.x);
    int y = (int) ceil(position.y);

    int gridx = x>>power;
    int gridy = y>>power;

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
    float centreX = 0.5*scale + scale*gridPosFx;
    float centreY = 0.5*scale + scale*gridPosFy;
    sf::Vector2f centre(centreX,centreY);

    return(centre);
}

sf::Vector2f Grid::getCentre(int x, int y)
{
    sf::Vector2i pos(x,y);
    return(getCentre(pos));
}

std::vector<GridSquare> Grid::getBox(sf::Vector2i tl, sf::Vector2i br)
{
    int l = tl.x;
    int r = br.x;
    int t = tl.y;
    int b = br.y;

    std::vector<GridSquare> ps;

    for(int i=l; i<=r; i++)
    {
         for(int j=t; j<=b; j++)
        {
            GridSquare g = getGridSquare(sf::Vector2i(i,j));
            ps.push_back(g);
            //debug->println("X: " + std::to_string(i) + " , Y: " + std::to_string(j) );
        }
    }
    return ps;

}

GridSquare Grid::getGridSquare(sf::Vector2i g)
{
    sf::Vector2f centre = getCentre(g);
    sf::FloatRect rect;
    rect.left = centre.x - 0.5*scale;
    rect.top = centre.y - 0.5*scale;
    rect.width = scale;
    rect.height = scale;

    GridSquare sq;

    sq.position = g;
    sq.region = rect;

    return sq;
}

void Grid::setDebug(DebugUtils *value)
{
    debug = value;
}
