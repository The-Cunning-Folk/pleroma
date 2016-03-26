#ifndef MATHSUTILS_H
#define MATHSUTILS_H

#include <random>
#include<time.h>
#include<functional>
#include<memory>
#include<iostream>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<convexpolygon.h>
#include<lineintersection.h>

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

    float min(float,float);
    float max(float,float);

    sf::FloatRect findIntersectionRegion(sf::FloatRect, sf::FloatRect);

    float getArea(sf::FloatRect);

    float fsin(float x);
    float fcos(float x);
    float ftan(float x);

    float fsinDeg(float x);
    float fcosDeg(float x);
    float ftanDeg(float x);

    int intDegRad(float x);
    int intDegDeg(float x);

    float fSqrt(float);

    float degToRad;
    float radToDeg;
    float pi;
    float tau;

    float round(float);
    int roundAndCast(float);

    int nxtPow2(int);
    int getPow2(int);

    float mag(sf::Vector2f);
    sf::Vector2f normal(sf::Vector2f);
    sf::Vector2f unit(sf::Vector2f);
    sf::Vector2f unitNormal(sf::Vector2f);

    float getBearing(sf::Vector2f);

    sf::Vector2f rotateClockwise(sf::Vector2f,float);
    ConvexPolygon rotateClockwise(ConvexPolygon &,float);

    sf::Vector2f rotateAntiClockwise(sf::Vector2f,float);
    ConvexPolygon rotateAntiClockwise(ConvexPolygon &,float);

    sf::Vector2i roundAndCast(sf::Vector2f);
    sf::Vector2f round(sf::Vector2f);

    float dot(sf::Vector2f,sf::Vector2f);

    ConvexPolygon scale(ConvexPolygon&,float);

    bool containsPoint(sf::Vector2f,ConvexPolygon&);
    LineIntersection findIntersection(sf::Vector2f,sf::Vector2f,ConvexPolygon&);

};
}

#endif // MATHSUTILS_H
