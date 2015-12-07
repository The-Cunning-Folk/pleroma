#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <collidable.h>
#include <SFML/Graphics.hpp>
#include <vector>

namespace BQ{
class QuadtreeNode : public sf::Drawable
{
public:
    QuadtreeNode();
    QuadtreeNode(sf::FloatRect);

    int level;
    void addObject(Collidable*);
    std::vector<Collidable*> objects;
    std::vector<QuadtreeNode> nodes;

    sf::FloatRect bounds;

    void split();
    void clear();

    void subdivide();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::RectangleShape rect;
        rect.setPosition(bounds.left+2,bounds.top+2);
        rect.setSize(sf::Vector2f(bounds.width-2,bounds.height-2));
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Cyan);
        rect.setFillColor(sf::Color::Transparent);
        target.draw(rect);
    }


};
}

#endif // QUADTREENODE_H
