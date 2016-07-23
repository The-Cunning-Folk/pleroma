#include "viewport.h"

using namespace BQ;

ViewPort::ViewPort()
{
    view.setSize(480,270);
    walkBox.height = 64;
    walkBox.width = 64;
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

void ViewPort::focus()
{
    Transform & t = componentLoader->getTransform(focusedTransform);
    view.setCenter(maths->round(t.position));
}

void ViewPort::update()
{
    float halfWidth = 0.5*walkBox.width;
    float halfHeight = 0.5*walkBox.height;

    walkBox.left = view.getCenter().x - halfWidth;
    walkBox.top = view.getCenter().y - halfHeight;

    Transform & t = componentLoader->getTransform(focusedTransform);

    sf::Vector2f pos = view.getCenter();
    sf::Vector2f focusPos = maths->round(t.position);
    sf::Vector2f diff = maths->round(t.position) - maths->round(pos);

    if(!walkBox.contains(t.position))
    {
        if(diff.x > halfWidth)
        {
            pos.x = focusPos.x-halfWidth;
        }
        else if(diff.x < -halfWidth)
        {
            pos.x = focusPos.x+halfWidth;
        }
        if(diff.y > halfHeight)
        {
            pos.y = focusPos.y-halfHeight;
        }
        else if(diff.y < -halfHeight)
        {
            pos.y = focusPos.y+halfHeight;
        }

        view.setCenter(pos);
    }





    sf::Vector2f windowSize = view.getSize();
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

