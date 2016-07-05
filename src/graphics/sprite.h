#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace BQ
{
class Sprite
{
public:
    Sprite();
    std::vector<sf::IntRect> frames;
    sf::Vector2i offset;
    float depthOffset;
};
}

#endif // SPRITE_H
