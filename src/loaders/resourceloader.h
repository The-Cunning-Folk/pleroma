#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <string>
#include <debugutils.h>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <sol.hpp>

namespace BQ{
class ResourceLoader
{
public:
    ResourceLoader();

    DebugUtils* debug;

    std::string loadFileAsString(std::string);

    rapidjson::Document loadJsonFile(std::string);
    sol::load_result loadLuaScript(sol::state& ,std::string);

    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);

    std::string baseDirectory;
    std::string fontDirectory;
    std::string textureDirectory;
    std::string scriptsDirectory;

    std::map<std::string,sf::Font> fonts;

    void loadConfig(std::string);

    std::map<std::string,sf::Texture> textures;

    sf::Font& getFont(std::string);
    sf::Texture& getTexture(std::string);

};
}

#endif // RESOURCELOADER_H
