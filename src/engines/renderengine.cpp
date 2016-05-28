#include "renderengine.h"

#include<game.h>

using namespace BQ;

RenderEngine::RenderEngine()
{

}


std::vector<SpriteRenderer> RenderEngine::getSprites() const
{
    return sprites;
}

void RenderEngine::setSprites(const std::vector<SpriteRenderer> &value)
{
    sprites = value;
}

BQ::SpriteRenderer &BQ::RenderEngine::addSpriteRenderer()
{
    sprites.resize(sprites.size()+1);
    sprites.back().index = sprites.size()-1;
    return sprites.back();
}

SpriteRenderer &RenderEngine::getSpriteRenderer(int index)
{
    if(index >=0 && index < sprites.size())
    {
        return sprites[index];
    }
    else
    {
        debug->printerr("requested spriterenderer out of bounds");
        return sprites[0]; //todo: this could cause a segfault! Very bad >:(
    }
}

void RenderEngine::wake()
{
    //load sprite sheets

    //load and parse textures.json
    std::string textureConfig = resourceLoader->loadFileAsString("config/textures.json");
    rapidjson::Document tconfig;
    tconfig.Parse(textureConfig.c_str());

    //get the parent directory for the spritesheets
    assert(tconfig["parentdirectory"].IsString());
    std::string tDir = tconfig["parentdirectory"].GetString();

    //load the spritesheets array
    const rapidjson::Value & files = tconfig["spritesheets"];
    assert(files.IsArray());

    for (rapidjson::SizeType i = 0; i < files.Size(); i++)
    {
        debug->println(tDir + "/" + files[i].GetString());
        std::string sheetConfig = resourceLoader->loadFileAsString(tDir + "/" + files[i].GetString());
        rapidjson::Document sConfig;
        sConfig.Parse(sheetConfig.c_str());

        assert(sConfig["name"].IsString());
        assert(sConfig["path"].IsString());
        assert(sConfig["sprites"].IsArray());

        std::string sName = sConfig["name"].GetString();
        std::string sDir = sConfig["path"].GetString();

        //construct a spritesheet object here
        if ( spriteSheets.find(sName) == spriteSheets.end() ) {
            debug->printwarn("duplicate sprite sheet defined in config: " + sName);
          // not found
        }

        spriteSheets[sName].texture = sDir;

    }



}

void BQ::RenderEngine::start()
{

}

void BQ::RenderEngine::run()
{

    for(int i=0; i<sprites.size(); i++)
    {
        SpriteRenderer & s = sprites[i];
        s.depth = componentLoader->getTransform(s.transform).position.y + s.depthOffset;
    }
}

void BQ::RenderEngine::finish()
{

}

void BQ::RenderEngine::drawDebug()
{


    std::vector<SpriteRenderer> renderList;

    for(int i=0; i<activeComponents.size(); i++)
    {
        SpriteRenderer s = sprites[activeComponents[i]];
        renderList.push_back(s);
    }

    std::sort(renderList.begin(),renderList.end());

    for(int i=0; i<renderList.size(); i++)
    {
        SpriteRenderer & s = renderList[i];
        sf::Sprite spr;
        spr.setTexture(resourceLoader->getTexture(s.texture));
        if(s.textureRect.width*s.textureRect.height != 0)
        {
            spr.setTextureRect(s.textureRect);
        }
        sf::Vector2f pos = componentLoader->getTransform(s.transform).position;
        if(s.centreOrigin)
        {
            pos.x -= 0.5*spr.getLocalBounds().width;
            pos.y -= 0.5*spr.getLocalBounds().height;
        }
        spr.setPosition(maths->round(pos + s.offset));
        gameWindow->draw(spr);
    }
}
