#include "pathingengine.h"

#include<game.h>

using namespace BQ;

PathingEngine::PathingEngine()
{

}

void PathingEngine::doWaveFront(sf::Vector2i start)
{
    //do a rolling wave work function calculation here

}

void PathingEngine::run()
{
    std::vector<GridSquare> & squares = grid->activeSquares;
    for(unsigned int i=0; i<squares.size(); i++)
    {
        GridSquare & g = squares[i];
        //do steps calculation
    }
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
        game->gameWindow->draw(t);
    }
}

