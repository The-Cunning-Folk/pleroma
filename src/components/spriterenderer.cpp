#include "spriterenderer.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;


SpriteRenderer::SpriteRenderer()
{
    transform = 0;
    offset.x = 0;
    offset.y = 0;
    texture = "error.png";
    centreOrigin = true;
}

int SpriteRenderer::getTransform() const
{
    return transform;
}

void SpriteRenderer::setTransform(int value)
{
    transform = value;
}

