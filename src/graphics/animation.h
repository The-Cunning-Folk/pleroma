#ifndef ANIMATION_H
#define ANIMATION_H

#include<frame.h>
#include<vector>

namespace BQ{
class Animation
{
public:
    Animation();

    bool running;
    bool stopped;

    float spf;
    float rate;
    sf::Clock clock;

    int frame;

    void update();
    void pause();
    void play();
    void stop();

};
}

#endif // ANIMATION_H
