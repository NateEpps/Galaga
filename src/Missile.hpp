//
// Missile.hpp
// Nathanael Epps
//

#ifndef MISSILE_HPP
#define MISSILE_HPP

#include <SFML/Graphics.hpp>

#include "Aimable.hpp"

class Missile : public sf::Drawable, public Aimable
{
public:
    Missile(sf::Vector2f, sf::Vector2f);
    
    void update(sf::Time);
    
    double getSpeedFactor() const;
    
    sf::FloatRect getGlobalBounds() const;
    
    virtual void move(double, double) override;
    
    virtual sf::Vector2f getPosition() const override;
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    static sf::Texture texture;
    
    sf::Sprite sprite;
    
    unsigned int direction;
};

#endif
