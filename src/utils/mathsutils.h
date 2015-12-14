#ifndef MATHSUTILS_H
#define MATHSUTILS_H

#include <random>
#include<time.h>
#include<functional>

namespace BQ{
class MathsUtils
{
public:
    MathsUtils();

    std::mt19937 twister;

    int randomInt(int,int);
    float randomFloat(float,float);

    int nxtPow2(int);
    int getPow2(int);
};
}

#endif // MATHSUTILS_H
