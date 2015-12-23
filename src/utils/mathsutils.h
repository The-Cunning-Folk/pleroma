#ifndef MATHSUTILS_H
#define MATHSUTILS_H

#include <random>
#include<time.h>
#include<functional>
#include<memory>
#include<iostream>
#include<math.h>

namespace BQ{
class MathsUtils
{
public:
    MathsUtils();

    std::mt19937 twister;

    int trigPrecision;

    int randomInt(int,int);
    float randomFloat(float,float);

    std::vector<float>sinTable;
    std::vector<float>cosTable;
    std::vector<float>tanTable;

    float fsin(float x);
    float fcos(float x);
    float ftan(float x);

    float fsinDeg(float x);
    float fcosDeg(float x);
    float ftanDeg(float x);

    int intDegRad(float x);
    int intDegDeg(float x);

    float degToRad;
    float radToDeg;

    float round(float);
    int roundAndCast(float);

    int nxtPow2(int);
    int getPow2(int);
};
}

#endif // MATHSUTILS_H
