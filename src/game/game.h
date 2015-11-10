#ifndef GAME_H
#define GAME_H

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

    void run();

private:

    DebugUtils debug;

    window_ptr gameWindow;

};
}
#endif // GAME_H
