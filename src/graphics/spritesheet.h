#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics.hpp>

namespace BQ{
class SpriteSheet
{
public:
    SpriteSheet();

    std::string texture;
    std::map<std::string,std::vector<sf::IntRect>> spriteFrames;
    std::map<int,std::string> spriteFrameMap;

    void addSprite(std::string,std::vector<sf::IntRect>);

    std::vector<sf::IntRect> & getSprite(std::string);
    std::vector<sf::IntRect> & getSprite(int);

};
}

#endif // SPRITESHEET_H
