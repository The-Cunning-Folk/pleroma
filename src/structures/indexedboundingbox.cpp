#include "indexedboundingbox.h"

using namespace BQ;

IndexedBoundingBox::IndexedBoundingBox()
{
    quadtreeLevel = 0;
}

IndexedBoundingBox::IndexedBoundingBox(const Collidable & c,int index)
{
    bBox = c.polygon.bBox;
    cIndex = index;
    quadtreeLevel = 0;
}

void IndexedBoundingBox::init(const Collidable & c, int index)
{
    bBox = c.polygon.bBox;
    cIndex = index;
    quadtreeLevel = 0;
}



