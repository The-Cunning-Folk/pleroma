#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <component.h>
#include <transform.h>


class Collidable : public Component
{
public:
    Collidable();

    Transform* transform;

    Transform *getTransform() const;
    void setTransform(Transform *value);

    sf::Rect bBox;

    sf::Rect getBBox() const;
    void setBBox(const sf::Rect &value);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

    }
};

#endif // COLLIDABLE_H
