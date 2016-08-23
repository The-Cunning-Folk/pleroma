#include "transformengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<gameobjectloader.h>
#include<game.h>


using namespace BQ;

TransformEngine::TransformEngine() : Engine()
{
    wrapAround = false;
    bounds = sf::FloatRect(0,0,480,270);
    placeholder = "auto_transform_";
}

void TransformEngine::start()
{

}

std::vector<std::string> TransformEngine::getObjectsInRange() const
{
    return objectsInRange;
}

void TransformEngine::setObjectsInRange(const std::vector<std::string> &value)
{
    objectsInRange = value;
}

sf::FloatRect TransformEngine::getBounds() const
{
    return bounds;
}

void TransformEngine::setBounds(const sf::FloatRect &value)
{
    bounds = value;
}

bool TransformEngine::getWrapAround() const
{
    return wrapAround;
}

void TransformEngine::setWrapAround(bool value)
{
    wrapAround = value;
}


void TransformEngine::run()
{
    GameObjectStore & os = game->getCurrentLevel().objects;
    int scale = grid->getScale();
    float rightEdge =(float) (bounds.left + bounds.width)*scale;
    float leftEdge =(float)  bounds.left*scale;
    float topEdge =(float)  bounds.top*scale;
    float bottomEdge =(float)  (bounds.top + bounds.height)*scale;

    activeComponents.clear();
    objectsInRange.clear();

    activeGridLocations = grid->activeSquares;


    for(it_transform it = os.transforms.begin(); it != os.transforms.end(); it++)
    {
        //update all the transforms!
        Transform & t = it->second;

        const sf::Vector2f & gpos = t.getPosition();
        if(bounds.contains(gpos))
        {
            activeComponents.push_back(it->first);
            objectsInRange.push_back(t.getParent());
        }


        if(wrapAround)
        {
            if(bounds.height>0 && bounds.width > 0)
            {

                if(leftEdge > gpos.x || rightEdge < gpos.x || topEdge > gpos.y || topEdge < gpos.y )
                {
                    //out of bounds
                    sf::Vector2f pos = t.getPosition();
                    if(pos.x > rightEdge)
                    {
                        t.setPosition(sf::Vector2f(leftEdge,pos.y));
                    }
                    if(pos.x < leftEdge)
                    {
                        t.setPosition(sf::Vector2f(rightEdge,pos.y));
                    }
                    pos = t.getPosition();
                    if(pos.y > bottomEdge)
                    {
                        t.setPosition(sf::Vector2f(pos.x,topEdge));
                    }
                    if(pos.y < topEdge)
                    {
                        t.setPosition(sf::Vector2f(pos.x,bottomEdge));
                    }
                }
            }
        }

    }



}

void TransformEngine::finish()
{

}

void TransformEngine::drawDebug()
{
    GameWindow& window = *gameWindow;

    sf::VertexArray gridDebug = sf::VertexArray(sf::Quads,grid->activeSquares.size()*4);

    for(unsigned int i =0; i<activeGridLocations.size();i++)
    {
        sf::FloatRect f = activeGridLocations[i].region;
        GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(activeGridLocations[i].position);

        gridDebug[i*4].position = sf::Vector2f(f.left + 1,f.top + 1);
        gridDebug[i*4].color = g.debugColor;
        gridDebug[i*4 + 1].position = sf::Vector2f(f.left + f.width - 1,f.top + 1);
        gridDebug[i*4 + 1].color = g.debugColor;
        gridDebug[i*4 + 2].position = sf::Vector2f(f.left + f.width - 1,f.top + f.height - 1);
        gridDebug[i*4 + 2].color = g.debugColor;
        gridDebug[i*4 + 3].position = sf::Vector2f(f.left + 1,f.top + f.width - 1);
        gridDebug[i*4 + 3].color = g.debugColor;
    }

    gameWindow->draw(gridDebug);

//    for(unsigned int j=0; j<activeComponents.size(); j++)
//    {
//        int i = activeComponents[j];
//        cross.setPosition(transforms[i].getPosition());
//        cross.update();
//        window.draw(cross);
    //    }
}

void TransformEngine::wake()
{
    GameObjectStore & os = game->getCurrentLevel().objects;
    for(it_transform it = os.transforms.begin(); it != os.transforms.end(); it++)
    {
        Transform & t = it->second;
        t.wake();
    }
}

void TransformEngine::runStep()
{
    GameObjectStore & os = game->getCurrentLevel().objects;
    for(unsigned int i=0; i<activeComponents.size(); i++)
    {
        int j = activeComponents[i];
        Transform & t = os.transforms[j];
        t.lastFrame = t.position;
        t.update();
        t.move(delta*(t.step));
        t.setGridPosition(grid->getGridPosition(t.getPosition()));
        t.step.x = t.step.y = 0;

    }
}

void TransformEngine::runCorrections()
{
    GameObjectStore & os = game->getCurrentLevel().objects;
    for(unsigned int i=0; i<activeComponents.size(); i++)
    {
        int j = activeComponents[i];
        Transform & t = os.transforms[j];
        t.move(t.correction);
        t.setGridPosition(grid->getGridPosition(t.getPosition()));
        t.correction.x = t.correction.y = 0;
    }
}
