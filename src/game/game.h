#ifndef GAME_H
#define GAME_H

#include <SFML/System/Sleep.hpp>
#include <memory>
#include <gamewindow.h>
#include <debugutils.h>

typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ
{
class Game
{
public:
    Game();

    void setGameWindow(window_ptr);
    window_ptr getGameWindow();

    void setFrameRate(float);
    float getFrameRate();

    void stabiliseFrameRate(float);

    void run();

private:

    DebugUtils debug;

    window_ptr gameWindow;

    float frameRate;
    float targetFrameDuration;

};
}
#endif // GAME_H
