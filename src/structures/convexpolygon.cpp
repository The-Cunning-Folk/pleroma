#include "convexpolygon.h"

//this class is a shape like sf::Intrect which is defined by a series of vectors

using namespace BQ;

ConvexPolygon::ConvexPolygon()
{
    points.resize(0);
    position.x = 0;
    position.y = 0;
}

void ConvexPolygon::addPoint(sf::Vector2f v)
{
    std::vector<sf::Vector2f> newpoints = points;
    newpoints.push_back(v);
    points = newpoints;
}

void ConvexPolygon::addPoint(float x, float y)
{
    addPoint(sf::Vector2f(x,y));
}

void ConvexPolygon::clearPoints()
{
    points.clear();
}

void ConvexPolygon::update()
{
    float totalX = 0.0;
    float totalY = 0.0;
    float avgX = 0.0;
    float avgY = 0.0;
    if(points.size() >= 1)
    {
        float left = points[0].x;
        float right = points[0].x;
        float top = points[0].y;
        float bottom = points[0].y;
        for(unsigned int i=1; i<points.size();i++)
        {
            sf::Vector2f & point = points[i];
            //bbox calculation
            float tx = point.x;
            float ty = point.y;
            //running average of positions
            totalX += tx;
            totalY += ty;
            if(tx < left)
            {
                left = tx;
            }
            if(tx > right)
            {
                right = tx;
            }
            if(ty < top)
            {
                top = ty;
            }
            if(ty > bottom)
            {
                bottom = ty;
            }
        }
        bBox.left = position.x + left;
        bBox.top = position.y + top;
        bBox.width = right - left;
        bBox.height = bottom - top;
        float fpoints = ((float)points.size());
        avgX = totalX/fpoints;
        avgY = totalY/fpoints;
        centreOffset = sf::Vector2f(avgX,avgY);
        centre = position + centreOffset;
    }
    else
    {
        bBox = sf::FloatRect(0,0,0,0);
    }
}

std::vector<sf::Vector2f> ConvexPolygon::getPoints() const
{
    return points;
}

void ConvexPolygon::setPoints(const std::vector<sf::Vector2f> &value)
{
    points = value;
}

sf::Vector2f ConvexPolygon::getPosition() const
{
    return position;
}

void ConvexPolygon::setPosition(const sf::Vector2f &value)
{
    position = value;
}
