#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <component.h>
#include <transform.h>

namespace BQ{
class Collidable : public Component
{
public:
    Collidable();

    int transform;

    int quadtreeLevel;

    sf::RectangleShape rectShape;

    sf::FloatRect bBox;

    void setBBoxRectColor(sf::Color);

    sf::FloatRect getBBox() const;
    void setBBox(const sf::FloatRect &value);

    void update();

    Transform & loadTransform();
    int getTransform() const;
    void setTransform(int value);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(rectShape);
    }
};
}

#endif // COLLIDABLE_H
