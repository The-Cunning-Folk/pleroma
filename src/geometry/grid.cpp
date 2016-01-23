#include "grid.h"

using namespace BQ;

Grid::Grid()
{
    setOrigin(0,0); //can't see myself ever wanting this to not be 0,0
    setScale(16);
    activeWidth = 0;
    activeOrigin.x =0;
    activeOrigin.y = 0;
    activeHeight = 0;
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

bool Grid::isActive(sf::Vector2i pos)
{
    int xpos = pos.x;
    int ypos = pos.y;
    if(xpos >= activeWidth || xpos < 0)
    {
        return false;
    }
    if( ypos >= activeHeight || ypos <0)
    {
        return false;
    }
    return true;
}

sf::Vector2i Grid::toLocalActiveCoords(sf::Vector2i v)
{
    sf::Vector2i l;

    l.x = v.x - activeOrigin.x;
    l.y = v.y - activeOrigin.y;

    return l;
}

GridSquare &Grid::getActiveGridSquareFromPosition(sf::Vector2f p)
{
    sf::Vector2i gPos = getGridPosition(p);
    return getActiveGridSquareFromGlobalCoords(gPos);
}

GridSquare &Grid::getActiveGridSquareFromGlobalCoords(sf::Vector2i global)
{
    sf::Vector2i local = toLocalActiveCoords(global);
    GridSquare & g = getActiveGridSquareFromLocalCoords(local);
    return g;
}

sf::Vector2i Grid::getActiveOrigin() const
{
    return activeOrigin;
}

void Grid::setActiveOrigin(const sf::Vector2i &value)
{
    activeOrigin = value;
}

GridSquare &Grid::getActiveGridSquareFromLocalCoords(sf::Vector2i p)
{
    int xpos = p.x;
    int ypos = p.y;

    if(!isActive(p))
    {
        return nullSqu;
    }

    int index = (xpos)*(activeHeight) + (ypos);
    GridSquare & g = activeSquares[index];
    return g;

}

std::vector<sf::Vector2i> Grid::getActiveNeighboursLocalCoords(sf::Vector2i p)
{
    int min_x = p.x-1;
    int max_x = p.x+1;
    int min_y = p.y-1;
    int max_y = p.y+1;

    std::vector<sf::Vector2i> neighbours;

    for(int i=min_x; i<=max_x; i++)
    {
        for(int j=min_y;j<=max_y;j++)
        {
            if(i==p.x && j==p.y){continue;}
            if(isActive(sf::Vector2i(i,j)))
            {
                neighbours.push_back(sf::Vector2i(i,j));
            }
        }
    }
    return neighbours;

}

std::vector<sf::Vector2i> Grid::bresenhamLine(sf::Vector2f, sf::Vector2f)
{
    std::vector<sf::Vector2i> squares(0);
    //add bresenham here
    return squares;
}

void Grid::setActiveBounds(sf::FloatRect bounds)
{
    activeSquares = getBox(getGridPosition(bounds.left,bounds.top),
                                          getGridPosition(bounds.left + bounds.width,
                                                                bounds.top + bounds.height));
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

    activeOrigin.x = l;
    activeOrigin.y = t;

    std::vector<GridSquare> ps;

    activeWidth = r-l+1;
    activeHeight = b-t+1;

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
