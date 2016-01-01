#ifndef ENGINE_H
#define ENGINE_H

#include<memory>
#include<vector>
#include<debugutils.h>
#include<mathsutils.h>
#include<gamewindow.h>

typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ{

class Game;
class EventFactory;
class ComponentLoader;
class GameObjectLoader;

class Engine
{
public:
    Engine();

    EventFactory* eventFactory;
    ComponentLoader* componentLoader;
    GameObjectLoader* gameObjectLoader;

    float delta;

    Game* game;

    DebugUtils* debug;
    MathsUtils* maths;

    std::string placeholder;
    int currentId;

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

    EventFactory *getEventFactory() const;
    void setEventFactory(EventFactory *value);

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

    Game *getGame() const;

    void setGame(Game *value);

    float getDelta() const;
    void setDelta(float value);

    MathsUtils *getMaths() const;
    void setMaths(MathsUtils *value);

    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);

protected:
    window_ptr gameWindow;

private:



};

}

#endif // ENGINE_H
