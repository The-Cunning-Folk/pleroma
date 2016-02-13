#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include<SFML/Graphics.hpp>

namespace BQ {
class GridSquare
{
public:
    GridSquare();

    int index;
    bool impassable;
    sf::Vector2i position;
    sf::FloatRect region;
    bool checked;
    int steps;
    int workSteps;
    std::vector<int> collidablesInContact;
    std::vector<std::string> objectsInContact;

    sf::Vector2f pathVector;

    void addCollidableInContact(int);
    void addObjectInContact(std::string);

};
}

#endif // GRIDSQUARE_H
