#include "mathsutils.h"

using namespace BQ;

MathsUtils::MathsUtils()
{
    twister.seed(time(0));
    trigPrecision = 3600;
    float fI;
    degToRad = 3.141/180.0;
    radToDeg = 1.0/degToRad;
    sinTable.resize(0);
    cosTable.resize(0);
    tanTable.resize(0);
    float prefact = degToRad/10;
    for(int i=0; i<trigPrecision; i++)
    {
        fI = ((float) i)*prefact;
        sinTable.push_back(sin(fI));
        cosTable.push_back(cos(fI));
        tanTable.push_back(tan(fI));
    }
}

int MathsUtils::randomInt(int l_bound, int u_bound)
{
    std::uniform_int_distribution<int> distribution(l_bound,u_bound);

    return distribution(twister);
}

float MathsUtils::randomFloat(float l_bound, float u_bound)
{
    std::uniform_real_distribution<float> distribution(l_bound,u_bound);

    return distribution(twister);
}

float MathsUtils::fsin(float x)
{
    return sinTable[intDegRad(x)];
}

float MathsUtils::fcos(float x)
{
    return cosTable[intDegRad(x)];
}

float MathsUtils::ftan(float x)
{
    return tanTable[intDegRad(x)];
}

float MathsUtils::fsinDeg(float x)
{
    return sinTable[intDegDeg(x)];
}

float MathsUtils::fcosDeg(float x)
{
    return cosTable[intDegDeg(x)];
}

float MathsUtils::ftanDeg(float x)
{
    return tanTable[intDegDeg(x)];
}

int MathsUtils::intDegRad(float x)
{
    return intDegDeg(x*radToDeg);
}

int MathsUtils::intDegDeg(float x)
{
    int iX = roundAndCast(x*10);
    while(iX >= 3600)
    {
        iX-=3600;
    }
    while(iX<0)
    {
        iX+= 3600;
    }
    return iX;
}

float MathsUtils::fSqrt(float x)
{

    unsigned int i = *(unsigned int*) &x;

  // adjust bias
  i  += 127 << 23;
  // approximation of square root
  i >>= 1;

  return *(float*) &i;
}

float MathsUtils::round(float x)
{
    float ceilX = ceil(x);
    float floorX = floor(x);
    float difC = ceilX - x;
    float difF = x - floorX;
    if(difF < difC) {return floorX;}
    else {return ceilX;}
}

int MathsUtils::roundAndCast(float x)
{
    float fR = round(x);
    return (int) fR;
}

int MathsUtils::nxtPow2(int x)
{
    if (x < 0)
    {
            return 0;
    }

    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x+1;
}

int MathsUtils::getPow2(int x)
{
    int pow = 0;
    while (((x & 1) == 0) && x > 1) /* While x is even and > 1 */
    {
       x >>= 1;
       pow ++;
    }
    return(pow);
}

float MathsUtils::mag(sf::Vector2f v)
{
    float sqMag = v.x*v.x + v.y*v.y;
    return fSqrt(sqMag);
}

sf::Vector2f MathsUtils::normal(sf::Vector2f v)
{
    return(sf::Vector2f(-v.y,v.x));
}

sf::Vector2f MathsUtils::unit(sf::Vector2f v)
{
    float vmag = mag(v);
    float rMag = 1/vmag;
    return(sf::Vector2f(v.x*rMag,v.y*rMag));
}

sf::Vector2f MathsUtils::unitNormal(sf::Vector2f v)
{
    return(unit(normal(v)));
}

float MathsUtils::dot(sf::Vector2f a, sf::Vector2f b)
{
    return(a.x*b.x+a.y*b.y);
}

