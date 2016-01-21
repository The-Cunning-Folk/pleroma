#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include<SFML/Graphics.hpp>

namespace BQ {
class GridSquare
{
public:
    GridSquare();

    sf::Vector2i position;
    sf::FloatRect region;
    int steps;
    int workSteps;
    std::vector<int> collidablesInContact;
    std::vector<std::string> objectsInContact;

};
}

#endif // GRIDSQUARE_H
