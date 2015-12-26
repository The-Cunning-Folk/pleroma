#ifndef PROJECTION_H
#define PROJECTION_H

#include<math.h>

namespace BQ{
class Projection
{
public:
    Projection();
    Projection(float,float);

    float max;
    float min;

    bool overlaps(const Projection &);
    float getOverlap(const Projection &);

};
}

#endif // PROJECTION_H
