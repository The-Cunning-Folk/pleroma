#include "floatrect.h"

FloatRect::FloatRect()
{

}

sf::FloatRect FloatRect::asSFFloatRect()
{
    sf::FloatRect sfRect;
    sfRect.width = width;
    sfRect.height = height;
    sfRect.left = left;
    sfRect.top = top;
    return sfRect;
}

