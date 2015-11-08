#include <iostream>
#include <SFML/Graphics.hpp>

#include <gamewindow.h>

using namespace std;

int main()
{
    GameWindow gameWindow(880,270,"ttest");

    gameWindow.run();

    return 0;
}
