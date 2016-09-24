#include "viewport.h"

#include <componentloader.h>
#include <mathsutils.h>

using namespace BQ;

ViewPort::ViewPort()
{
    view.setSize(480,270);
    bounds.left = 0;
    bounds.top = 0;
    bounds.width = 1024;
    bounds.height = 1024;
    walkBox.height = 64;
    walkBox.width = 64;
}

sf::FloatRect ViewPort::getBounds() const
{
    return bounds;
}

void ViewPort::setBounds(const sf::FloatRect &value)
{
    bounds = value;
}

sf::FloatRect ViewPort::getWalkBox() const
{
    return walkBox;
}

void ViewPort::setWalkBox(const sf::FloatRect &value)
{
    walkBox = value;
}

MathsUtils *ViewPort::getMaths() const
{
    return maths;
}

void ViewPort::setMaths(MathsUtils *value)
{
    maths = value;
}

ComponentLoader *ViewPort::getComponentLoader() const
{
    return componentLoader;
}

void ViewPort::setComponentLoader(ComponentLoader *value)
{
    componentLoader = value;
}

sf::FloatRect ViewPort::getRenderRegion() const
{
    return renderRegion;
}

void ViewPort::setRenderRegion(const sf::FloatRect &value)
{
    renderRegion = value;
}

void ViewPort::rescaleMaintainingRatio(float width, float height)
{


}

void ViewPort::rescale(float width, float height)
{
    view.setSize(width,height);
}

void ViewPort::focus()
{
    Transform & t = componentLoader->getTransform(focusedTransform);

    sf::Vector2f pos = t.position;

    sf::Vector2f windowSize = view.getSize();
    float halfViewWidth = 0.5*windowSize.x;
    float halfViewHeight = 0.5*windowSize.y;

    if(pos.y + halfViewHeight > bounds.top + bounds.height)
        pos.y = bounds.top + bounds.height - halfViewHeight;

    if(pos.y - halfViewHeight < bounds.top)
        pos.y = bounds.top + halfViewHeight;

    if(pos.x + halfViewWidth > bounds.left + bounds.width)
        pos.x = bounds.left + bounds.width - halfViewWidth;

    if(pos.x - halfViewWidth < bounds.left)
        pos.x = bounds.left + halfViewWidth;

    view.setCenter(maths->round(pos));
}

void ViewPort::update()
{
    float halfWidth = 0.5*walkBox.width;
    float halfHeight = 0.5*walkBox.height;

    sf::Vector2f windowSize = view.getSize();

    float halfViewWidth = 0.5*windowSize.x;
    float halfViewHeight = 0.5*windowSize.y;

    walkBox.left = view.getCenter().x - halfWidth;
    walkBox.top = view.getCenter().y - halfHeight;

    Transform & t = componentLoader->getTransform(focusedTransform);

    sf::Vector2f pos = view.getCenter();
    sf::Vector2f focusPos = maths->round(t.position);
    sf::Vector2f diff = maths->round(t.position) - maths->round(pos);

    if(!walkBox.contains(t.position))
    {
        if(pos.x + halfViewWidth <= bounds.left + bounds.width && pos.x - halfViewWidth >= bounds.left)
        {
            if(diff.x > halfWidth)
            {
                pos.x = focusPos.x-halfWidth;
            }
            else if(diff.x < -halfWidth)
            {
                pos.x = focusPos.x+halfWidth;
            }
        }
        if(pos.y + halfViewHeight <= bounds.top + bounds.height && pos.y - halfViewHeight >= bounds.top)
        {
            if(diff.y > halfHeight)
            {
                pos.y = focusPos.y-halfHeight;
            }
            else if(diff.y < -halfHeight)
            {
                pos.y = focusPos.y+halfHeight;
            }
        }
        if(pos.y + halfViewHeight > bounds.top + bounds.height)
            pos.y = bounds.top + bounds.height - halfViewHeight;

        if(pos.y - halfViewHeight < bounds.top)
            pos.y = bounds.top + halfViewHeight;

        if(pos.x + halfViewWidth > bounds.left + bounds.width)
            pos.x = bounds.left + bounds.width - halfViewWidth;

        if(pos.x - halfViewWidth < bounds.left)
            pos.x = bounds.left + halfViewWidth;

        view.setCenter(pos);
    }






    sf::FloatRect windowAbs = sf::FloatRect(view.getCenter().x-0.5*windowSize.x,
                                            view.getCenter().y-0.5*windowSize.y,
                                            windowSize.x,
                                            windowSize.y);

    sf::FloatRect rendAbs = sf::FloatRect(view.getCenter().x-windowSize.x,
                                          view.getCenter().y-windowSize.y,
                                          2*windowSize.x,
                                          2*windowSize.y);

    renderRegion = rendAbs;

    drawRegion = windowAbs;
}

sf::FloatRect ViewPort::getDrawRegion() const
{
    return drawRegion;
}

void ViewPort::setDrawRegion(const sf::FloatRect &value)
{
    drawRegion = value;
}

