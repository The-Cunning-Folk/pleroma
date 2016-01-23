#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include<SFML/Graphics.hpp>

namespace BQ {
class GridSquare
{
public:
    GridSquare();

    int index;
    sf::Vector2i position;
    sf::FloatRect region;
    bool checked;
    int steps;
    int workSteps;
    std::vector<int> collidablesInContact;
    std::vector<std::string> objectsInContact;
    sf::Vector2f pathVector;

};
}

#endif // GRIDSQUARE_H
