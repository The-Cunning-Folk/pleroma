#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include <SFML/Graphics.hpp>


class CustomShape : public sf::Drawable
{
public:
    CustomShape();

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &value);

    sf::Vector2f position;

private:



    virtual void update()
    {

    }
};

#endif // CUSTOMSHAPE_H
