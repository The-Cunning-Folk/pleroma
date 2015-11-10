#include "windowmanager.h"


using namespace BQ;

WindowManager::WindowManager()
{

}

window_ptr WindowManager::addWindow(std::string tag,int width,int height,std::string name)
{
    window_ptr newWindow(new GameWindow(width,height,name));  //define a new shared pointer

    newWindow->setTag(tag);

    gameWindows.push_back(newWindow); //give it to the window manager to handle creation and destruction

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
