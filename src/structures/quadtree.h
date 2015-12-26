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

    std::vector<QuadtreeNode> flatNodes;

    void initialise();
    void initialiseNode(QuadtreeNode &);

    sf::FloatRect getRegion() const;
    void setRegion(const sf::FloatRect &value);

    void addObject(const Collidable &, int index);

    void clear();

    void buildNode(QuadtreeNode &);
    void drawNode(sf::RenderTarget &target, const QuadtreeNode &) const;

    void build();

private:

};
}
#endif // QUADTREE_H
