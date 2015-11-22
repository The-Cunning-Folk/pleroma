#include "crossshape.h"

CrossShape::CrossShape()
{
    lineLength = 10;
    halfLength = 0.5*lineLength;
    horizLine.setOrigin(halfLength,1);
    horizLine.setSize(sf::Vector2f(lineLength,2));
    vertLine.setOrigin(1,halfLength);
    vertLine.setSize(sf::Vector2f(2,lineLength));
    update();
}

void CrossShape::update()
{
    vertLine.setPosition(position.x,position.y);
    horizLine.setPosition(position.x,position.y);
}

