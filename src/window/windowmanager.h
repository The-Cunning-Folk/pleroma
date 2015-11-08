#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <gamewindow.h>

namespace BQ {
    class WindowManager
    {
    public:
        WindowManager();

        void addWindow(std::string,int,int,std::string);
        void removeWindow(std::string);

        void run();

    private:
        std::vector<BQ::GameWindow*> gameWindows;
    };
}

#endif // WINDOWMANAGER_H
