#ifndef OCCLUSIONMANAGER_H
#define OCCLUSIONMANAGER_H

#include <vector>

#include <componentloader.h>
#include <gameobjectloader.h>


namespace BQ{

class Game;

class OcclusionManager
{
public:
    OcclusionManager();

    std::vector<std::string> activeObjects;
    std::vector<std::string> drawObjects;

    sf::Vector2i tl;
    sf::Vector2i br;

    ComponentLoader* componentLoader;
    GameObjectLoader* gameObjectLoader;

    Game* game;

    std::vector<int> getActiveComponents(std::string);

    Game *getGame() const;
    void setGame(Game *value);
    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);
    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);
    std::vector<std::string> getDrawObjects() const;
    void setDrawObjects(const std::vector<std::string> &value);
    std::vector<std::string> getActiveObjects() const;
    void setActiveObjects(const std::vector<std::string> &value);
    sf::Vector2i getTl() const;
    void setTl(const sf::Vector2i &value);
    sf::Vector2i getBr() const;
    void setBr(const sf::Vector2i &value);
};
}

#endif // OCCLUSIONMANAGER_H
