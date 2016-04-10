#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <string>
#include <debugutils.h>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace BQ{
class ResourceLoader
{
public:
    ResourceLoader();

    DebugUtils* debug;


    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);

    std::string baseDirectory;
    std::string fontDirectory;
    std::string textureDirectory;

    std::map<std::string,sf::Font> fonts;

    std::map<std::string,sf::Texture> textures;

    sf::Font& getFont(std::string);
    sf::Texture& getTexture(std::string);

};
}

#endif // RESOURCELOADER_H
