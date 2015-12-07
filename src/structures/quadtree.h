#ifndef QUADTREE_H
#define QUADTREE_H

#include <quadtreenode.h>

namespace BQ{
class Quadtree : public sf::Drawable
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

    void addObject(Collidable*);

    void clear();

    void buildNode(QuadtreeNode &);
    void drawNode(sf::RenderTarget &target, const QuadtreeNode &) const;

    void build();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
}
#endif // QUADTREE_H
