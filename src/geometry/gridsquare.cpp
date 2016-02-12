#include "gridsquare.h"

using namespace BQ;

GridSquare::GridSquare()
{
    steps=-1;
    workSteps=-1;
    checked = false;
    impassable = false;
}

void GridSquare::addCollidableInContact(int i)
{
    collidablesInContact.push_back(i);
}

void GridSquare::addObjectInContact(std::string o)
{
    objectsInContact.push_back(o);
}

