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
    
    sprite.emplace(texture);
    SetSize(sprite.value(), sprite.value().getGlobalBounds(), width, height);
    
    direction = GetDirection(vStart, vTarget);
    
    sprite.value().setRotation(sf::degrees((direction + 270) % 360));
    
    sprite.value().setPosition(vStart);
}

double Missile::getSpeedFactor() const
{
    return 1.0 / AngleToSlope(direction);
}

void Missile::update(sf::Time dt)
{
#warning Missile::update: Magic number 
    static constexpr float Adjust = 5;

    moveAtAngle(direction, dt.asMilliseconds() * getSpeedFactor() * Adjust);
}

sf::FloatRect Missile::getGlobalBounds() const
{
    return sprite.value().getGlobalBounds();
}

void Missile::move(float dx, float dy)
{
    sprite.value().move({dx, dy});
}

sf::Vector2f Missile::getPosition() const
{
    return sprite.value().getPosition();
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite.value(), states);
}
