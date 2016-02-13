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

void PathingEngine::calculateFlowVectors()
{


    for(int i=grid->tl.x; i<= grid->br.x; i++)
    {
        for(int j = grid->tl.y; j<=grid->br.y; j++)
        {

            GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(sf::Vector2i(i,j));
            std::vector<sf::Vector2i> adjacents = grid->getNeighboursAndDiagonals(g);
            sf::Vector2f resultant(0,0);

            if(g.steps > 0)
            {
                int minSteps = INT_MAX;
                for(int i=0; i<adjacents.size(); i++)
                {

                    GridSquare & n = grid->getActiveGridSquareFromLocalCoords(adjacents[i]);
                    sf::Vector2f diff = grid->getCentre(n.position) - grid->getCentre(g.position);
                    if(n.steps < minSteps && n.steps >= 0 && n.steps < g.steps)
                    {

                        minSteps = n.steps;
                        resultant = diff;
                     }
                }
            }

            g.pathVector =resultant;
        }
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
    calculateFlowVectors();


    goals.clear();
}

void PathingEngine::drawDebug()
{
    std::vector<GridSquare> & squares = grid->activeSquares;

    sf::VertexArray pathVectors(sf::Lines);

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

        pathVectors.append(txtpos);
        pathVectors.append(txtpos + g.pathVector);

        //game->gameWindow->draw(t);
    }

    game->gameWindow->draw(pathVectors);
}

