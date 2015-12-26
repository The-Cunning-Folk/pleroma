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
    return((max > p.min && min < p.max));
}

float Projection::getOverlap(const Projection & p)
{
    bool lowest = min < p.min;
    bool highest = max > p.max;
    float correction = 0;

    if((lowest && highest) || (!lowest && !highest))
    {
        float mins = fabs(min - p.min);
        float maxs = fabs(max - p.max);
        if(mins<maxs)
        {
            correction = mins;
        }
        else
        {
            correction = maxs;
        }
    }
    if(lowest)
    {
        return fabs(max - p.min + correction);
    }
    else
    {
        return fabs(p.max - min + correction);
    }
}

