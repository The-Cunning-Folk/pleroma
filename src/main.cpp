#include <iostream>
#include <SFML/Graphics.hpp>

#include <windowmanager.h>

using namespace std;

int main()
{
    BQ::WindowManager windowManager;

    windowManager.addWindow("game",480,270,"Dev Build");

    windowManager.run();

    return 0;
}
