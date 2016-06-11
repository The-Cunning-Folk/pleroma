#include "animation.h"

using namespace BQ;

Animation::Animation()
{
    frame = 0;
    rate = 1.0f;
    running = true;
    spf = 0.120f;
}

void Animation::update()
{

    if(!running)
    {
        clock.restart();
    }
    if(rate*clock.getElapsedTime().asSeconds() >= spf)
    {
        frame++;
        clock.restart();
    }
}

void Animation::pause()
{
    running = false;
}

void Animation::play()
{
    running = true;
}

void Animation::stop()
{
    running = false;
    frame = 0;
}

