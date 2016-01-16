#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include <engine.h>
#include <transform.h>
#include <grid.h>

namespace BQ{

class TransformEngine : public Engine
{
public:
    TransformEngine();

    CrossShape cross;

    Grid* grid;

    std::vector<std::string> objectsInRange;

    bool wrapAround;
    sf::FloatRect bounds;

    void run();
    void drawDebug();

    void updatePositions();

    std::vector<Transform> transforms;
    std::vector<sf::Vector2i> activeGridLocations;

    Transform& addTransform();

    Grid *getGrid() const;
    void setGrid(Grid *value);
    bool getWrapAround() const;
    void setWrapAround(bool value);

    Transform & getTransform(int);
    sf::FloatRect getBounds() const;
    void setBounds(const sf::FloatRect &value);
    std::vector<std::string> getObjectsInRange() const;
    void setObjectsInRange(const std::vector<std::string> &value);
    std::vector<sf::Vector2i> getActiveGridLocations() const;
    void setActiveGridLocations(const std::vector<sf::Vector2i> &value);
};
}

#endif // TRANSFORMENGINE_H
