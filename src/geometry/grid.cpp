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
    nullSqu.workFunction = 1E10;
    nullSqu.steps = 1E10;
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

    if(xpos*activeHeight + ypos > activeSquares.size()-1)
    {
        return false;
    }
    return true;
}

bool Grid::isActiveGlobal(sf::Vector2i pos)
{
    int xpos = pos.x;
    int ypos = pos.y;
    if(xpos > br.x || xpos < tl.x)
    {
        return false;
    }
    if( ypos >= br.y || ypos < tl.y)
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
        if(i==p.x) {continue;}
        if(isActive(sf::Vector2i(i,p.y)))
        {
                neighbours.push_back(sf::Vector2i(i,p.y));
        }
    }
    for(int i=min_y; i<=max_y; i++)
    {
        if(i==p.y) {continue;}
        if(isActive(sf::Vector2i(p.x,i)))
        {
                neighbours.push_back(sf::Vector2i(p.x,i));
        }
    }
    return neighbours;

}

std::vector<sf::Vector2i> Grid::getActiveNeighboursAndDiagonalsLocalCoords(sf::Vector2i p)
{

    int min_x = p.x-1;
    int max_x = p.x+1;
    int min_y = p.y-1;
    int max_y = p.y+1;

    std::vector<sf::Vector2i> neighbours;

    for(int i=min_x; i<=max_x; i++)
    {
        for(int j=min_y; j<=max_y; j++)
        {
            if(i==p.x && j == p.y) {continue;}
            if(isActive(sf::Vector2i(i,j)))
            {
                    neighbours.push_back(sf::Vector2i(i,j));
            }
        }
    }
    return neighbours;

}


std::vector<sf::Vector2i> Grid::getNeighbours(GridSquare & g)
{
    sf::Vector2i p = g.position;
    return getActiveNeighboursLocalCoords(toLocalActiveCoords(p));
}

std::vector<sf::Vector2i> Grid::getNeighboursAndDiagonals(GridSquare & g)
{
    sf::Vector2i p = g.position;
    return getActiveNeighboursAndDiagonalsLocalCoords(toLocalActiveCoords(p));
}

std::vector<sf::Vector2i> Grid::bresenhamLine(sf::Vector2f a, sf::Vector2f b)
{

    std::vector<sf::Vector2i> squares;

    sf::Vector2f diff = b - a;

    sf::Vector2f unit = math.unit(diff);

    sf::Vector2f step;

    float distance = math.mag(diff);

    float stepMag = math.min(distance*0.1f,1.0f);

    step = stepMag*unit;

    int stepCount = (int) ceil(distance/stepMag);

    sf::Vector2i lastGridPos = getGridPosition(a);
    squares.push_back(lastGridPos);

    for(int i; i<stepCount-1; i++)
    {
        sf::Vector2f stepPos = a + ((float) i)*step;

        sf::Vector2i thisGridPos = getGridPosition(stepPos);
        if(thisGridPos != lastGridPos)
        {
            squares.push_back(thisGridPos);
        }
    }

    sf::Vector2i endGridPos = getGridPosition(b);

    if(endGridPos != lastGridPos)
    {
        squares.push_back(lastGridPos);
    }

    return squares;
}

std::vector<sf::Vector2i> Grid::bresenhamPolygonEdge(ConvexPolygon & polygon)
{

    std::vector<sf::Vector2i> gridEdges;

    for(int i=1; i<polygon.points.size(); i++)
    {
        std::vector<sf::Vector2i> edge = bresenhamLine(polygon.position + polygon.points[i],
                                                             polygon.position + polygon.points[i-1]);

        for(int j=0; j<edge.size(); j++)
        {
            bool alreadyPresent = false;
            for(int k=0; k<gridEdges.size(); k++)
            {
                if(edge[j]==gridEdges[k]){
                    alreadyPresent = true;
                }
            }
            if(!alreadyPresent)
            {
                gridEdges.push_back(edge[j]);
            }
        }

    }
    if(polygon.points.size() > 2){
        std::vector<sf::Vector2i> edge = bresenhamLine(polygon.position + polygon.points[0],
                                                             polygon.position + polygon.points[polygon.points.size()-1]);
        for(int j=0; j<edge.size(); j++)
        {
            bool alreadyPresent = false;
            for(int k=0; k<gridEdges.size(); k++)
            {
                if(edge[j]==gridEdges[k]){
                    alreadyPresent = true;
                }
            }
            if(!alreadyPresent)
            {
                gridEdges.push_back(edge[j]);
            }
        }
    }

    return gridEdges;
}

void Grid::setActiveBounds(sf::FloatRect bounds)
{
    tl = getGridPosition(bounds.left,bounds.top);
    br = getGridPosition(bounds.left + bounds.width,
                         bounds.top + bounds.height);
    activeSquares = getBox(tl,br);

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

std::vector<GridSquare> Grid::getBox(sf::FloatRect rect)
{
    sf::Vector2i tl = getGridPosition(rect.left,rect.top);
    sf::Vector2i br = getGridPosition(rect.left+rect.width,rect.top+rect.height);

    return getBox(tl,br);

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
            g.index = ps.size();
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
