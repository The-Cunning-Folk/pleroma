#include "transformengine.h"

#include<eventfactory.h>
#include<componentloader.h>

using namespace BQ;

TransformEngine::TransformEngine() : Engine()
{
    wrapAround = false;
    bounds = sf::IntRect(0,0,0,0);
    placeholder = "auto_transform_";
}

sf::IntRect TransformEngine::getBounds() const
{
    return bounds;
}

void TransformEngine::setBounds(const sf::IntRect &value)
{
    bounds = value;
}

Transform & TransformEngine::getTransform(int index)
{
    return transforms[index];
}

bool TransformEngine::getWrapAround() const
{
    return wrapAround;
}

void TransformEngine::setWrapAround(bool value)
{
    wrapAround = value;
}

Grid *TransformEngine::getGrid() const
{
    return grid;
}

void TransformEngine::setGrid(Grid *value)
{
    grid = value;
}

void TransformEngine::run()
{
    int scale = grid->getScale();
    float rightEdge =(float) (bounds.left + bounds.width)*scale;
    float leftEdge =(float)  bounds.left*scale;
    float topEdge =(float)  bounds.top*scale;
    float bottomEdge =(float)  (bounds.top + bounds.height)*scale;

    for(unsigned int i=0; i<transforms.size(); i++)
    {
        //update all the transforms!
        if(wrapAround)
        {
            if(bounds.height>0 && bounds.width > 0)
            {
                if(!bounds.contains(transforms[i].getGridPosition()))
                {
                    sf::Vector2f pos = transforms[i].getPosition();
                    if(pos.x > rightEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(leftEdge,pos.y));
                    }
                    if(pos.x < leftEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(rightEdge,pos.y));
                    }
                    pos = transforms[i].getPosition();
                    if(pos.y > bottomEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(pos.x,topEdge));
                    }
                    if(pos.y < topEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(pos.x,bottomEdge));
                    }
                }
            }
        }


        transforms[i].update();
        transforms[i].setGridPosition(grid->getGridPosition(transforms[i].getPosition()));
    }
}

void TransformEngine::drawDebug()
{
    for(unsigned int i=0; i<transforms.size(); i++)
    {
        //draw all the transforms!
        gameWindow->draw(transforms[i]);
    }
}

Transform *TransformEngine::addTransform()
{
    transforms.resize(transforms.size() + 1);
    if(debug != NULL){
        transforms.back().setDebug(debug);
    }
    transforms.back().index = transforms.size()-1;
    transforms.back().name = placeholder + std::to_string(currentId);
    currentId++;
    return(&transforms.back());
}
