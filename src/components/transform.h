#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<component.h>
#include<crossshape.h>

namespace BQ {

class Transform : public Component
{
public:

    Transform();

    //CrossShape cross;

    sf::Vector2i gridPosition; //the position of the object on the grid

    sf::Vector2f lastFrame;
    sf::Vector2f position; //this is the position that we do work on so that we can scale things nicely
    sf::Vector2f size;
    sf::Vector2f velocity;
    sf::Vector2f step;
    sf::Vector2f correction;

    std::vector <int> children; //transforms that are bound to this one

    void move(sf::Vector2f);
    void move(sf::Vector2i);
    void move(float,float);

    sf::FloatRect getBBox();

    sf::Vector2i getGridPosition() const;
    void setGridPosition(const sf::Vector2i &value);

    sf::Vector2f getPosition() const;

    void update();
    void wake();

    sf::Vector2i getWindowPosition() const;
    void setWindowPosition(const sf::Vector2i &value);

    void setPosition(const sf::Vector2f &value);
    void setPosition(float,float);

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &value);

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f &value);

    sf::Vector2f getLastFrame() const;
    void setLastFrame(const sf::Vector2f &value);

private:

    sf::Vector2i windowPosition; //this is the actual position of the object to avoid sprite tearing

};

}

#endif // TRANSFORM_H
