#include "pathingengine.h"

#include<game.h>

using namespace BQ;

PathingEngine::PathingEngine()
{
    goals.resize(0);
}

void PathingEngine::doWaveFront(GridSquare & start)
{
    //do a rolling wave work function calculation here
    start.checked = true;
    start.steps+=1;

    std::vector<sf::Vector2i> neighbours = grid->getNeighbours(start);

    for(int i=0; i<neighbours.size(); i++)
    {
         GridSquare & g = grid->getActiveGridSquareFromLocalCoords(neighbours[i]);
         g.steps = start.steps+1;
         g.checked = true;
    }

    doWaveFrontLayer(start.steps+1,neighbours);

}

void PathingEngine::doWaveFrontLayer(int layerNum, std::vector<sf::Vector2i> layer)
{
    std::vector<sf::Vector2i> nextLayer;
    for(unsigned int i=0; i< layer.size(); i++)
    {
        GridSquare & g = grid->getActiveGridSquareFromLocalCoords(layer[i]);
        std::vector<sf::Vector2i> thisNeighbours = grid->getNeighbours(g);
        for(unsigned int j=0; j<thisNeighbours.size(); j++)
        {
            GridSquare & n = grid->getActiveGridSquareFromLocalCoords(thisNeighbours[j]);
            if(!n.checked)
            {
                if(!n.impassable)
                {
                    n.steps = layerNum+1;
                    n.checked = true;
                    nextLayer.push_back(grid->toLocalActiveCoords(n.position));
                }
                else
                {
                    n.steps = -1;
                    n.checked = true;
                }
            }
        }
    }
    if(nextLayer.size() > 0)
    {
        doWaveFrontLayer(layerNum+1,nextLayer);
    }
}


void PathingEngine::addGoal(sf::Vector2f p)
{
    goals.push_back(p);
}

void PathingEngine::run()
{
    for(unsigned int i=0; i<goals.size(); i++)
    {
        doWaveFront(grid->getActiveGridSquareFromPosition(goals[i]));
    }
    goals.clear();
}

void PathingEngine::drawDebug()
{
    std::vector<GridSquare> & squares = grid->activeSquares;
    for(unsigned int i=0; i<squares.size(); i++)
    {
        GridSquare & g = squares[i];
        sf::Vector2f txtpos = grid->getCentre(g.position);
        sf::Text t;
        t.setPosition(txtpos.x - 5, txtpos.y - 5);
        t.setFont(resourceLoader->getFont("8bit16.ttf"));
        t.setCharacterSize(8);
        t.setString(std::to_string(g.steps));
        t.setColor(sf::Color::Magenta);
        game->gameWindow->draw(t);
    }
}

