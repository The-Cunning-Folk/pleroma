#ifndef FLOATRECT_H
#define FLOATRECT_H

#include <SFML/Graphics.hpp>


class FloatRect
{
public:
    FloatRect();
    float left;
    float top;
    float width;
    float height;

    sf::FloatRect asSFFloatRect();
};

#endif // FLOATRECT_H
