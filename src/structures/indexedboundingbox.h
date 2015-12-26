#ifndef INDEXEDBOUNDINGBOX_H
#define INDEXEDBOUNDINGBOX_H

#include <collidable.h>
#include <SFML/Graphics.hpp>

namespace BQ{
class IndexedBoundingBox
{
public:
    IndexedBoundingBox();
    IndexedBoundingBox(const Collidable &,int);

    void init(const Collidable &,int);

    sf::FloatRect bBox;
    int cIndex;
    int quadtreeLevel;
};
}

#endif // INDEXEDBOUNDINGBOX_H
