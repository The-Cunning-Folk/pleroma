#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<component.h>
#include<crossshape.h>

namespace BQ {

class Transform : public Component
{
public:

    Transform();

    CrossShape cross;

    sf::Vector2i gridPosition; //the position of the object on the grid

    sf::Vector2f position; //this is the position that we do work on so that we can scale things nicely
    sf::Vector2f size;

    sf::FloatRect getBBox();

    std::vector <Transform*> children; //transforms that are bound to this one

    void move(sf::Vector2f);
    void move(sf::Vector2i);
    void move(float,float);
    void move(int,int);

    sf::Vector2i getGridPosition() const;
    void setGridPosition(const sf::Vector2i &value);

    sf::Vector2f getPosition() const;

    void update();

    sf::Vector2i getWindowPosition() const;
    void setWindowPosition(const sf::Vector2i &value);

    void setPosition(const sf::Vector2f &value);

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &value);

private:

    sf::Vector2i windowPosition; //this is the actual position of the object to avoid sprite tearing

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(cross);
    }
};

}

#endif // TRANSFORM_H
