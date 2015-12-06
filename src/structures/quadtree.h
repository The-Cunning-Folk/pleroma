#ifndef QUADTREE_H
#define QUADTREE_H

#include <quadtreenode.h>

namespace BQ{
class Quadtree
{
public:
    Quadtree();

    int maxLevels;
    int maxObjects;

    sf::FloatRect region;

    QuadtreeNode parentNode;

    sf::FloatRect getRegion() const;
    void setRegion(const sf::FloatRect &value);

    void addObject(Collidable*);

    void clear();

    void build();
};
}
#endif // QUADTREE_H
