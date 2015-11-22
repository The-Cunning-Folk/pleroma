#ifndef CROSSSHAPE_H
#define CROSSSHAPE_H

#include <customshape.h>


class CrossShape : public CustomShape
{
public:
    CrossShape();

    sf::RectangleShape vertLine;
    sf::RectangleShape horizLine;

    int lineLength;
    int halfLength;

    void update();

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(vertLine);
        target.draw(horizLine);
    }

};

#endif // CROSSSHAPE_H
