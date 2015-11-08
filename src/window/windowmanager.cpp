#include "windowmanager.h"


using namespace BQ;

WindowManager::WindowManager()
{

}

void WindowManager::addWindow(std::string tag,int width,int height,std::string name)
{
    gameWindows.push_back(new GameWindow(width,height,name));
}

void WindowManager::removeWindow(std::string)
{

}

void WindowManager::run()
{

    bool anyWindowOpen = false;

    for(unsigned int i = 0; i<gameWindows.size(); i++)
    {
        BQ::GameWindow &window = *gameWindows[i];

        if(window.isOpen()){
            anyWindowOpen = true;
        }
    }

    while (anyWindowOpen)
    {

        for(unsigned int i = 0; i<gameWindows.size(); i++)
        {
            BQ::GameWindow &window = *gameWindows[i];
            //window management
            sf::Event event;
            while (window.window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

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
