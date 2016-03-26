#ifndef GRID_H
#define GRID_H

#include<SFML/Graphics.hpp>
#include<mathsutils.h>
#include<debugutils.h>

#include<gridsquare.h>

namespace BQ {
class Grid
{
public:

    /* grid positions are defined from their top left corner
     * this means that the grid position 0,0 corresponds to a rect from tl(0f,0f) to br(scale,scale)
     * this comment is here if you're ever working drunk and forget
     * */

    Grid();

    GridSquare nullSqu; // an ugly way to handle errors safely. Should NEVER have to be used!

    int getScale() const;
    void setScale(int value);

    sf::Vector2i getOrigin() const;
    void setOrigin(const sf::Vector2i &value);
    void setOrigin(int,int);

    int activeWidth;
    int activeHeight;

    sf::Vector2i tl;
    sf::Vector2i br;

    sf::Vector2i activeOrigin;

    bool isActive(sf::Vector2i);
    bool isActiveGlobal(sf::Vector2i);

    sf::Vector2i toLocalActiveCoords(sf::Vector2i);

    GridSquare & getActiveGridSquareFromPosition(sf::Vector2f);

    GridSquare & getActiveGridSquareFromGlobalCoords(sf::Vector2i);

    GridSquare & getActiveGridSquareFromLocalCoords(sf::Vector2i);

    std::vector<sf::Vector2i> getActiveNeighboursLocalCoords(sf::Vector2i);

    std::vector<sf::Vector2i> getActiveNeighboursAndDiagonalsLocalCoords(sf::Vector2i);

    std::vector<sf::Vector2i> getNeighbours(GridSquare &);

    std::vector<sf::Vector2i> getNeighboursAndDiagonals(GridSquare &);

    std::vector<sf::Vector2i> bresenhamLine(sf::Vector2f,sf::Vector2f);
    std::vector<sf::Vector2i> bresenhamPolygonEdge(ConvexPolygon &);

    std::vector<GridSquare> activeSquares;

    void setActiveBounds(sf::FloatRect);

    //todo: layering
    //I'm not totally decided on how I'm handling layers at this stage
    sf::Vector3i getGridPosition(sf::Vector2f, int); //where am I on the grid with height?

    sf::Vector2i getGridPosition(sf::Vector2f); //where am I on the grid without height?
    sf::Vector2i getGridPosition(float,float);
    int getGridLayer(float); //get my height with just a float

    sf::Vector2f getCentre(sf::Vector2i);
    sf::Vector2f getCentre(int,int);
    float getLayerMidPoint(int); // get the float for the halfway point of a layer

    std::vector<GridSquare> getBox(sf::Vector2i,sf::Vector2i); // get all the grid positions in a box
    std::vector<GridSquare> getBox(sf::FloatRect);
    GridSquare getGridSquare(sf::Vector2i);

    void setDebug(DebugUtils *value);

    std::vector<GridSquare> getActiveSquares() const;
    void setActiveSquares(const std::vector<GridSquare> &value);

    sf::Vector2i getActiveOrigin() const;
    void setActiveOrigin(const sf::Vector2i &value);

private:

    int scale; // this must be a power of 2 so I can bitshift
    int power; //the power of 2 that the scale is
    sf::Vector2i origin; //the actual position of grid(0,0)

    //passed from game
    DebugUtils* debug;

    //owns its own maths instance for speed
    MathsUtils math;

};
}

#endif // GRID_H
