#include "pathingengine.h"

#include<game.h>

using namespace BQ;

PathingEngine::PathingEngine()
{
    goals.resize(0);
}

void PathingEngine::doWaveFront(sf::Vector2i start)
{
    //do a rolling wave work function calculation here

    sf::Vector2i localStart = grid->toLocalActiveCoords(start);
    std::vector<sf::Vector2i> neighbours = grid->getActiveNeighboursLocalCoords(localStart);

    for(unsigned int i=0; i<neighbours.size(); i++)
    {
        grid->getActiveGridSquareFromLocalCoords(neighbours[i]).steps=1;
    }

}

void PathingEngine::addGoal(sf::Vector2f p)
{
    goals.push_back(p);
}

void PathingEngine::run()
{
    std::vector<GridSquare> & squares = grid->activeSquares;
    for(unsigned int i=0; i<squares.size(); i++)
    {
        GridSquare & g = squares[i];
        //do steps calculation
    }
    for(unsigned int i=0; i<goals.size(); i++)
    {
        doWaveFront(grid->getActiveGridSquareFromPosition(goals[i]).position);
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

