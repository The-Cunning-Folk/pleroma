#include <iostream>
#include <SFML/Graphics.hpp>

#include <windowmanager.h>

using namespace std;

int main()
{
    BQ::WindowManager windowManager;

    windowManager.addWindow("first",480,270,"test");
    windowManager.addWindow("second",480,270,"test2");
    windowManager.run();
    return 0;
}
