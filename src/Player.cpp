//
// Player.cpp
// Nathanael Epps
//

#include "Player.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "ControllerPanel.hpp"
#include "Rss/Rss.hpp"
#include "Util.hpp"

using namespace sf;

static const int AmtMissilesAllowed = 2;

// #define MOVE_UP_DOWN

Player::Player()
{
    rss_t sBytes = getResourceShipPng();
    if (!sTexture.loadFromMemory(sBytes.data, sBytes.size))
        throw MakeException("Could not load ship texture data");
    
    self.setTexture(sTexture);
    
    Vector2u wsize = GetLastWindow()->getSize();
    
    SetSize(self, getBounds(), wsize.x * 0.05, wsize.x * 0.05);
    
    rss_t mBytes = getResourcePlayerMissilePng();
    if (!mTexture.loadFromMemory(mBytes.data, mBytes.size))
        throw MakeException("Could not load player missile data");
    
    //                          |||
    // mTexture set on creation vvv
}

#ifdef DEBUG

Player::~Player()
{
    Print("Amount of projectiles: ", missiles.size());
}

#endif

void Player::process(sf::Event event)
{
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
    {
        if (missiles.size() >= AmtMissilesAllowed)
            return;
        
        Sprite sprite;
        Vector2u wsize = GetLastWindow()->getSize();
        float sizex = wsize.x * 0.01;
        float sizey = sizex * 2.0;
        
        sprite.setTexture(mTexture);
        
        SetSize(sprite, sprite.getGlobalBounds(), sizex, sizey);
        
        Vector2f pos = getPosition();
        pos.y -= sizey;
        pos.x += getBounds().width / 2;
        pos.x -= sizex / 2.0;
        
        sprite.setPosition(pos);
        
        missiles.push_back(sprite);
    }
}

void Player::update(sf::Time dt)
{
    int dx = 0, dy = 0;
#ifdef MOVE_UP_DOWN
    if (Keyboard::isKeyPressed(Keyboard::Down))
        dy = 1;
    else if (Keyboard::isKeyPressed(Keyboard::Up))
        dy = -1;
#endif
    if (Keyboard::isKeyPressed(Keyboard::Left))
        dx = -1;
    else if (Keyboard::isKeyPressed(Keyboard::Right))
        dx = 1;
    
    self.move(dx * dt.asMilliseconds(), dy * dt.asMilliseconds());
    
    // don't go offscreen...
    OffscreenGuard(self, Vector2f(getBounds().width, getBounds().height));
    
    // ... or past this line
#warning Rethink this part
    static const Vector2u wsize = GetLastWindow()->getSize();
    static const float bound = wsize.y * 0.6;
    if (self.getPosition().y < bound)
        self.setPosition(self.getPosition().x, bound + 1);
    
    // handle missiles
    if (missiles.size() == 0)
        return;
    
    bool shouldPop = false;
    
    for (Sprite& ref : missiles) {
        ref.move(0, -1 * dt.asMilliseconds());
        
        if (ref.getPosition().y < (-2 * ref.getGlobalBounds().height)) {
            if (shouldPop)
                throw MakeException("Trying to pop multiple projectiles");
            
            shouldPop = true;
        }
    }
    
    if (shouldPop) {
        missiles.pop_front();
    }
}

std::vector<FloatRect> Player::getMissileBounds() const
{
    std::vector<FloatRect> vec;
    for (const auto& missile : missiles)
        vec.push_back(missile.getGlobalBounds());
    
    return vec;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(self, states);
    
    for (const auto& ref : missiles)
        target.draw(ref, states);
}
