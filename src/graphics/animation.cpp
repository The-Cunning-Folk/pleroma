#include "animation.h"

using namespace BQ;

Animation::Animation()
{
    frame = 0;
    rate = 1.0f;
    running = true;
    spf = 0.120f;
    stopped = false;
}

void Animation::update()
{

    if(!running || stopped)
    {
        clock.restart();
    }

    if(stopped)
    {
        frame = 0;
    }
    else if(running && !stopped && rate*clock.getElapsedTime().asSeconds() >= spf)
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
    stopped = false;
    running = true;
}

void Animation::stop()
{
    stopped = true;
    running = false;
}

