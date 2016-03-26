#include "mathsutils.h"

using namespace BQ;

MathsUtils::MathsUtils()
{
    twister.seed(time(0));
    trigPrecision = 3600;
    float fI;
    pi = 3.141;
    tau = pi*2.0;
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

float MathsUtils::min(float a, float b)
{
    if(a<=b)
    {
        return a;
    }
    else {
        return b;
    }
}

float MathsUtils::max(float a, float b)
{
    if(a>=b)
    {
        return a;
    }
    else {
        return b;
    }
}

sf::FloatRect MathsUtils::findIntersectionRegion(sf::FloatRect a, sf::FloatRect b)
{
    float l;
    float t;
    if(b.left+b.width - a.left < a.left+a.width-b.left){
        l=a.left;
    }
    else{
        l=b.left;
    }
    if(b.top+b.height - a.top < a.top+a.height-b.top){
        t = a.top;
    }
    else{
        t =b.top;
    }

    float width = min(b.left+b.width-l,a.left+a.width-l);
    float height = min(b.top+b.height-t,a.top+a.height-t);

    return sf::FloatRect(l,t,width,height);
}

float MathsUtils::getArea(sf::FloatRect r)
{
    return r.width*r.height;
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

float MathsUtils::getBearing(sf::Vector2f v)
{
    return atan2(-v.y,v.x); //from nvidia library
}

sf::Vector2f MathsUtils::rotateClockwise(sf::Vector2f v, float rads)
{
    sf::Vector2f v2;
    float c = fcos(rads);
    float s = fsin(rads);
    v2.x = c*v.x + s*v.y;
    v2.y = -s*v.x + c*v.y;
    return(v2);
}

ConvexPolygon MathsUtils::rotateClockwise(ConvexPolygon & c,float rads)
{
    std::vector<sf::Vector2f> points = c.getPoints();
    ConvexPolygon nc;
    for(int i = 0; i<points.size(); i++)
    {
        sf::Vector2f p = rotateClockwise(points[i],rads);
        nc.addPoint(p);
    }
    return nc;
}

sf::Vector2f MathsUtils::rotateAntiClockwise(sf::Vector2f v, float rads)
{
    sf::Vector2f v2;
    float c = fcos(rads);
    float s = fsin(rads);
    v2.x = c*v.x - s*v.y;
    v2.y = s*v.x + c*v.y;
    return(v2);
}

ConvexPolygon MathsUtils::rotateAntiClockwise(ConvexPolygon & c, float rads)
{
    std::vector<sf::Vector2f> points = c.getPoints();
    ConvexPolygon nc;
    for(int i = 0; i<points.size(); i++)
    {
        sf::Vector2f p = rotateAntiClockwise(points[i],rads);
        nc.addPoint(p);
    }
    return nc;
}

sf::Vector2i MathsUtils::roundAndCast(sf::Vector2f v)
{
    sf::Vector2i vi = sf::Vector2i(roundAndCast(v.x),roundAndCast(v.y));
    return vi;
}

sf::Vector2f MathsUtils::round(sf::Vector2f v)
{
    sf::Vector2f vf = sf::Vector2f(round(v.x),round(v.y));
    return vf;
}

float MathsUtils::dot(sf::Vector2f a, sf::Vector2f b)
{
    return(a.x*b.x+a.y*b.y);
}

ConvexPolygon MathsUtils::scale(ConvexPolygon & c, float factor)
{
    std::vector<sf::Vector2f> points = c.getPoints();
    ConvexPolygon nc;
    for(int i = 0; i<points.size(); i++)
    {
        sf::Vector2f p = factor*points[i];
        nc.addPoint(p);
    }
    return nc;
}

bool MathsUtils::containsPoint(sf::Vector2f p, ConvexPolygon & c)
{
    bool contained = false;
    int i,j = 0;
    for(i = 0, j = c.points.size()-1; i < c.points.size(); j = i++)
    {
        sf::Vector2f vi = c.position + c.points[i];
        sf::Vector2f vj = c.position + c.points[j];
        if( ((vi.y > p.y)!=(vj.y>p.y)) && (p.x < (vj.x-vi.x) * (p.y-vi.y) / (vj.y-vi.y) + vi.x) )
        {
            contained = !contained;
        }
    }
    return contained;
}

LineIntersection MathsUtils::findIntersection(sf::Vector2f a, sf::Vector2f b, ConvexPolygon& c)
{
    LineIntersection intersection;

    sf::Vector2f diff = b - a;
    sf::Vector2f unitV = unit(diff);
    sf::Vector2f step;
    float stepMag = 1.0f;
    step = stepMag*unitV;
    float distance = mag(diff);
    int stepCount = (int) ceil(distance);

    for(int i=0; i<stepCount; i++)
    {
        sf::Vector2f stepPos = a + ((float) i)*step;
        if(containsPoint(stepPos,c))
        {
            intersection.intersects = true;
            intersection.intersectionPoint = stepPos;
            return intersection;
        }
    }
    return intersection;

}

