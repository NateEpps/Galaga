//
// Enemy.cpp
// Nathanael Epps
//

#include <cmath>

#include "Enemy.hpp"
#include "Util.hpp"

using namespace sf;

Enemy::Enemy(const Texture& t)
{
    self.setTexture(t);
    
    auto wsize = GetLastWindow()->getSize();
    
    SetSize(self, self.getGlobalBounds(), wsize.x * 0.06, wsize.x * 0.05);
    
    shouldDraw = true;
    
    speedFactor = 1;
    
    hasFired = false;
}

#ifdef DRAW_TARGETS

void Enemy::addPoint(float x, float y)
{
    path.emplace(x, y);
    
    static Vector2u wsize = GetLastWindow()->getSize();
    static const int Radius = wsize.x * 0.005;
    CircleShape target;
    
    target.setRadius(Radius);
    target.setFillColor(Color::Red);
    target.setOrigin(Radius, Radius);
    target.setPosition(x, y);
    
    drawpath.push_back(target);
}

void Enemy::clearPoints()
{
    // clear the path
    std::queue<sf::Vector2f>().swap(path);
    
    drawpath.clear();
}

#endif

Vector2f Enemy::getCurrentPoint() const
{
    if (path.empty())
        throw MakeException("Path queue is empty");
    
    return path.front();
}

void Enemy::update(sf::Time dt)
{
    // move the enemy along it's path
    if (!path.empty()) {
        moveTowards(path.front(), dt.asMilliseconds());
        
        static const auto wsize = GetLastWindow()->getSize();
        
        if (IsClose(self.getPosition(), path.front(), wsize.x * 0.02)) {
            setPosition(path.front());
            path.pop();
        }
    }
    
    // update any missiles currently in flight
    for (Missile& m : missiles)
        m.update(dt);
    
    // get rid of missiles that go offscreen
    missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [](const Missile& m) {
        return m.getPosition().y > (GetLastWindow()->getSize().y + 10);
    }), missiles.end());
}

void Enemy::fireAt(sf::Vector2f target)
{
    if (hasFired)
        return;
    
    static const double YOffset = GetLastWindow()->getSize().x * 0.14;
    
    int amtMissiles = RandInt(2, 3);
    
    if (amtMissiles == 2) {
        Vector2f left = target;
        Vector2f right = target;
        left.x -= YOffset / 2;
        right.x += YOffset / 2;
        
        missiles.emplace_back(self.getPosition(), left);
        missiles.emplace_back(self.getPosition(), right);
    }
    else {
        Vector2f left = target;
        Vector2f right = target;
        left.x -= YOffset;
        right.x += YOffset;
        
        missiles.emplace_back(self.getPosition(), left);
        missiles.emplace_back(self.getPosition(), target);
        missiles.emplace_back(self.getPosition(), right);
    }
    
    hasFired = true;
}

void Enemy::setSpeedFactor(float f)
{
#warning Check f, use something other then "assert"
    // assert(f > 0);
    
    speedFactor = f;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (shouldDraw) {
        target.draw(self, states);
        for (const Missile& m : missiles)
            target.draw(m, states);
#ifdef DRAW_TARGETS
        for (const Drawable& t : drawpath)
            target.draw(t, states);
#endif
    }
}
