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

void ViewPort::update()
{
    walkBox.left = view.getCenter().x - 0.5*walkBox.width;
    walkBox.top = view.getCenter().y - 0.5*walkBox.height;

    Transform & t = componentLoader->getTransform(focusedTransform);



    if(!walkBox.contains(t.position))
    {

        sf::Vector2f pos = view.getCenter();
        sf::Vector2f diff = t.position - pos;

        float diffY = abs(diff.y);
        float diffX = abs(diff.x);

        if(diffY > 0.5*walkBox.height) //player has walked too far in y
        {

            if(diff.y > 0) //player has moved down
            {
                pos.y += diffY - 0.5*walkBox.height;
            }
            else //player has moved up
            {
                pos.y -= diffY - 0.5*walkBox.height;
            }
        }

        if(diffX > 0.5*walkBox.width)//player has walked too far in x
        {

            if(diff.x > 0) //player has moved right
            {
                pos.x += diffX - 0.5*walkBox.width;
            }
            else //player has moved left
            {
                pos.x -= diffX - 0.5*walkBox.width;
            }
        }

        view.setCenter(maths->round(pos));
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
}

sf::FloatRect ViewPort::getDrawRegion() const
{
    return drawRegion;
}

void ViewPort::setDrawRegion(const sf::FloatRect &value)
{
    drawRegion = value;
}

