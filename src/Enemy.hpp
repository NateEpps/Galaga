//
// Enemy.hpp
// Nathanael Epps
//

#ifndef ENEMY_HPP
#define ENEMY_HPP

//#define DRAW_TARGETS

#include <deque>
#include <queue>

#include <SFML/Graphics.hpp>

#include "Aimable.hpp"
#include "Rss/Rss.hpp"
#include "Missile.hpp"

class Enemy : public sf::Drawable, public Aimable
{
public:
    explicit Enemy(const sf::Texture&);
#ifdef DRAW_TARGETS
    void addPoint(float, float);
    
    void clearPoints();
#endif
    sf::Vector2f getCurrentPoint() const;
    
    void update(sf::Time);
    
    void fireAt(sf::Vector2f);
    
    void setSpeedFactor(float);
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    //////////////////////////////////////////////////////////////////////////////
    
    inline void addPoint(sf::Vector2f v) { addPoint(v.x, v.y); }
#ifndef DRAW_TARGETS
    inline void addPoint(float x, float y) { path.emplace(x, y); }
#endif
    inline bool hasPoints() const { return !path.empty(); }
#ifndef DRAW_TARGETS
    inline void clearPoints() { std::queue<sf::Vector2f>().swap(path); }
#endif
    inline void show() { shouldDraw = true; }
    inline void hide() { shouldDraw = false; }
    
    inline void pop() { path.pop(); }
    
    inline std::deque<Missile>& getMissilesRef() { return missiles; }
    
    //////////////////////////////////////////////////////////////////////////////
    
    // Fake transformable
    
    inline void setPosition(float x, float y) { self.setPosition(x, y); }
    inline void setPosition(sf::Vector2f v) { self.setPosition(v); }
    virtual sf::Vector2f getPosition() const override { return self.getPosition(); }
    
    inline sf::FloatRect getBounds() const { return self.getGlobalBounds(); }
    
    virtual void move(double dx, double dy) override { self.move(dx, dy); }
    
private:
    sf::Sprite self;
    std::queue<sf::Vector2f> path;
    bool shouldDraw;
    float speedFactor;
    std::deque<Missile> missiles;
    bool hasFired;
#ifdef DRAW_TARGETS
    std::deque<sf::CircleShape> drawpath;
#endif
};

#endif
