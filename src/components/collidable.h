#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <component.h>
#include <transform.h>

namespace BQ{
class Collidable : public Component
{
public:
    Collidable();

    Transform* transform;

    Transform *getTransform() const;
    void setTransform(Transform *value);

    sf::RectangleShape rectShape;

    sf::FloatRect bBox;

    sf::FloatRect getBBox() const;
    void setBBox(const sf::FloatRect &value);

    void update();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(rectShape);
    }
};
}

#endif // COLLIDABLE_H
