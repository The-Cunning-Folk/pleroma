#include "resourceloader.h"

using namespace BQ;

ResourceLoader::ResourceLoader()
{
    baseDirectory = "var";
    fontDirectory = "fonts";
}

DebugUtils *ResourceLoader::getDebug() const
{
    return debug;
}

void ResourceLoader::setDebug(DebugUtils *value)
{
    debug = value;
}

sf::Font &ResourceLoader::getFont(std::string name)
{
    std::map<std::string,sf::Font>::const_iterator it = fonts.find(name);
    bool exists = it!=fonts.end();
    if(exists) {return fonts[name];}

    //the font is not in the map

    sf::Font font;

    //only load the font if it's not present in the map
    if(!font.loadFromFile(baseDirectory + "/" + fontDirectory + "/" + name))
    {
        debug->println("font not found");
        debug->printerr("font not found");
    }
    fonts[name] = font;
    return fonts[name];
}

