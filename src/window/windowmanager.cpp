#include "windowmanager.h"


using namespace BQ;

WindowManager::WindowManager()
{

}

window_ptr WindowManager::addWindow(std::string tag,int width,int height,std::string name)
{
    window_ptr newWindow(new GameWindow(width,height,name));  // p1 owns Foo
    gameWindows.push_back(newWindow);
    return(newWindow);
}

void WindowManager::removeWindow(std::string)
{

}

bool WindowManager::anyOpen(){
    bool anyWindowOpen = false;
    for(unsigned int i = 0; i<gameWindows.size(); i++)
    {
        BQ::GameWindow &window = *gameWindows[i];

        if(window.isOpen()){
            anyWindowOpen = true;
        }
    }
    return(anyWindowOpen);
}

void WindowManager::run()
{

    bool anyWindowOpen = true;

    while (anyWindowOpen)
    {

        anyWindowOpen = anyOpen();

        for(unsigned int i = 0; i<gameWindows.size(); i++)
        {
            BQ::GameWindow &window = *gameWindows[i];
            //event management

            window.updateEvents();

            //end window management

            if(window.isOpen()){
                window.clear();
            }

            //drawing goes here

            window.draw();

            //end drawing

            if(window.isOpen()){
                window.display();
            }


        }
    }

}
