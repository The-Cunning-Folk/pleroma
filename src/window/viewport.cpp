#include "viewport.h"

using namespace BQ;

ViewPort::ViewPort()
{
    view.setSize(480,270);
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

void ViewPort::update()
{
    Transform & t = componentLoader->getTransform(focusedTransform);
    view.setCenter(maths->round(t.position));
    sf::Vector2f windowSize = view.getSize();
    sf::FloatRect windowAbs = sf::FloatRect(view.getCenter().x-0.5*windowSize.x,
                                            view.getCenter().y-0.5*windowSize.y,
                                            windowSize.x,
                                            windowSize.y);

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

