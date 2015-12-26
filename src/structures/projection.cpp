#include "projection.h"

using namespace BQ;

Projection::Projection()
{

}

Projection::Projection(float min, float max)
{
    this->min = min;
    this->max = max;
}

bool Projection::overlaps(const Projection & p)
{
    return(max > p.min && min < p.max);
}

float Projection::getOverlap(const Projection & p)
{
    bool lowest = min <= p.min;
    if(lowest)
    {
        return fabs(max - p.min);
    }
    else
    {
        return fabs(p.max - min);
    }
}

