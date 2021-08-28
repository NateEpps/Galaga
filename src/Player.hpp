//
// Player.hpp
// Nathanael Epps
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <deque>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Player : public sf::Drawable
{
public:
    Player();
#ifdef DEBUG
    virtual ~Player();
#endif
    void process(sf::Event);
    
    void update(sf::Time);
    
    std::vector<sf::FloatRect> getMissileBounds() const;
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    ////////////////////////////////////////////////////////////////////////
    
    inline size_t getAmtMissiles() const { return missiles.size(); }
    
    inline void setPosition(float x, float y) { self.setPosition(x, y); }
    inline void setPosition(sf::Vector2f v) { self.setPosition(v); }
    inline sf::Vector2f getPosition() const { return self.getPosition(); }
    
    inline void move(float dx, float dy) { self.move(dx, dy); }
    
    inline sf::FloatRect getBounds() const { return self.getGlobalBounds(); }
    
    ////////////////////////////////////////////////////////////////////////
    
    friend class GamePanel;
    
private:
    sf::Sprite self;
    sf::Texture sTexture;
    sf::Texture mTexture;
    
    std::deque<sf::Sprite> missiles;
};

#endif
