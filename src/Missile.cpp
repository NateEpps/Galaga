//
// Missile.cpp
// Nathanael Epps
//

#include "Missile.hpp"

#include "Rss/Rss.hpp"
#include "Util.hpp"

using namespace sf;

/*static*/ Texture Missile::texture;

Missile::Missile(sf::Vector2f vStart, sf::Vector2f vTarget)
{
    static bool init = false;
    if (!init) {
        auto resource = getResourceEnemyMissilePng();
        if (!texture.loadFromMemory(resource.data, resource.size))
            throw MakeException("Could not load resource");
        
        init = true;
    }
    
    auto wsize = GetLastWindow()->getSize();
    
    double width = wsize.x * 0.01;
    double height = width * 2;
    
    sprite.setTexture(texture);
    SetSize(sprite, sprite.getGlobalBounds(), width, height);
    
    direction = GetDirection(vStart, vTarget);
    
    sprite.setRotation((direction + 270) % 360);
    
    sprite.setPosition(vStart);
}

double Missile::getSpeedFactor() const
{
    return 1.0 / AngleToSlope(direction);
}

void Missile::update(sf::Time dt)
{
    moveAtAngle(direction, dt.asMilliseconds() * getSpeedFactor());
}

sf::FloatRect Missile::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

void Missile::move(double dx, double dy)
{
    sprite.move(dx, dy);
}

sf::Vector2f Missile::getPosition() const
{
    return sprite.getPosition();
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
