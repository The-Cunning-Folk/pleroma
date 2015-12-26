#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <string>
#include <debugutils.h>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>


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

    std::map<std::string,sf::Font> fonts;

    sf::Font& getFont(std::string);

};
}

#endif // RESOURCELOADER_H
