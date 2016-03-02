#include "gridsquare.h"

using namespace BQ;

GridSquare::GridSquare()
{
    steps=-1;
    workFunction=0;
    checked = false;
    impassable = false;
    pathVector.x = 0;
    pathVector.y = 0;
    debugColor = sf::Color::Blue;
}

void GridSquare::addCollidableInContact(int i)
{
    collidablesInContact.push_back(i);
}

void GridSquare::addObjectInContact(std::string o)
{
    objectsInContact.push_back(o);
}

