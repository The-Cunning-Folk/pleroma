#include "resourceloader.h"

using namespace BQ;

ResourceLoader::ResourceLoader()
{
    baseDirectory = "";
    fontDirectory = "fonts";
    textureDirectory = "textures";
}

std::string ResourceLoader::loadFileAsString(std::string path)
{
    std::ifstream ifs(baseDirectory + "/" + path);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
    return content;
}

rapidjson::Document ResourceLoader::loadJsonFile(std::string path)
{
    std::string jsonStr = loadFileAsString(path);
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());
    return doc;
}

DebugUtils *ResourceLoader::getDebug() const
{
    return debug;
}

void ResourceLoader::setDebug(DebugUtils *value)
{
    debug = value;
}

void ResourceLoader::loadConfig(std::string path)
{
    std::ifstream ifs(path);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
    rapidjson::Document config;
    config.Parse(content.c_str());

    if(config.HasMember("base_directory"))
    {
        baseDirectory = config["base_directory"].GetString();
    }
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
        debug->printerr("font " + name + " not found");
    }
    fonts[name] = font;
    return fonts[name];
}

sf::Texture &ResourceLoader::getTexture(std::string name)
{
    std::map<std::string,sf::Texture>::const_iterator it = textures.find(name);
    bool exists = it!=textures.end();
    if(exists) {return textures[name];}

    //the texture is not in the map

    sf::Texture texture;

    if(name == "")
    {
        texture.loadFromFile(baseDirectory + "/" + textureDirectory + "/" + "error.png");
        return texture;
    }

    if(!texture.loadFromFile(baseDirectory + "/" + textureDirectory + "/" + name))
    {
        debug->println("texture " + baseDirectory + "/" + textureDirectory + "/" + name + " not found");
        texture.loadFromFile(baseDirectory + "/" + textureDirectory + "/" + "error.png");
    }

    textures[name] = texture;
    return textures[name];

}

