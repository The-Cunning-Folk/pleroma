#ifndef ENGINE_H
#define ENGINE_H

#include<memory>
#include<vector>
#include<debugutils.h>

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

    DebugUtils *getDebug() const;
    void setDebug(DebugUtils *value);
};

}

#endif // ENGINE_H
