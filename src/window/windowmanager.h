#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <memory>
#include <gamewindow.h>

typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ {
    class WindowManager
    {
    public:
        WindowManager();

        //window management
        window_ptr addWindow(std::string,int,int,std::string);
        window_ptr addWindow(std::string,int,int,std::string,int);

        void removeWindow(std::string);


        //runtime
        bool anyOpen();


    private:
        std::vector<window_ptr> gameWindows;
    };
}

#endif // WINDOWMANAGER_H
