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

void BQ::RenderEngine::start()
{

}

void BQ::RenderEngine::run()
{

    for(int i=0; i<sprites.size(); i++)
    {
        SpriteRenderer & s = sprites[i];
        s.depth = componentLoader->getTransform(s.transform).position.y;
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
        spr.setPosition(pos + s.offset);
        gameWindow->draw(spr);
    }
}
