#ifndef ENGINE_H
#define ENGINE_H

#include<memory>
#include<vector>
#include<debugutils.h>
#include<gamewindow.h>

typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ{

class Engine
{
public:
    Engine();



    DebugUtils* debug;

    virtual void run(){
        if(debug != NULL){
            debug->printerr("undefined engine.run()");
        }
    }

    virtual void drawDebug(){
        if(debug != NULL){
            debug->printerr("undefined engine.drawDebug()");
        }
    }


    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);

    window_ptr getGameWindow() const;
    void setGameWindow(const window_ptr &value);

protected:
    window_ptr gameWindow;

private:



};

}

#endif // ENGINE_H
