#ifndef PROJECTION_H
#define PROJECTION_H

namespace BQ{
class Projection
{
public:
    Projection();
    Projection(float,float);

    float max;
    float min;

    bool overlaps(const Projection &);

};
}

#endif // PROJECTION_H
