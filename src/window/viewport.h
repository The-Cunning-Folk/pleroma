#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SFML/Graphics.hpp>



namespace BQ{

class ComponentLoader;
class MathsUtils;

class ViewPort
{
public:
    ViewPort();

    ComponentLoader * componentLoader;
    MathsUtils * maths;

    int focusedTransform;

    sf::View view;
    sf::FloatRect drawRegion;
    sf::FloatRect renderRegion;

    sf::FloatRect walkBox;
    sf::FloatRect bounds;

    sf::FloatRect getDrawRegion() const;
    void setDrawRegion(const sf::FloatRect &value);
    sf::FloatRect getRenderRegion() const;
    void setRenderRegion(const sf::FloatRect &value);

    void rescaleMaintainingRatio(float,float);
    void rescale(float,float);

    void focus();

    void update();

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);
    MathsUtils *getMaths() const;
    void setMaths(MathsUtils *value);
    sf::FloatRect getWalkBox() const;
    void setWalkBox(const sf::FloatRect &value);
    sf::FloatRect getBounds() const;
    void setBounds(const sf::FloatRect &value);
};
}

#endif // VIEWPORT_H
