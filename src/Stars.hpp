//
// Stars.hpp
// Nathanael Epps
//

#ifndef STARS_HPP
#define STARS_HPP

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Stars : public sf::Drawable
{
public:
    explicit Stars(const int);
    
    void update(sf::Time);
    
    virtual void draw(sf::RenderTarget&,
                      sf::RenderStates) const override;
    
    // inline void start() { isOn = true; }
    void restart();
    
    inline void stop() { isOn = false; }
    
private:
    struct StarStruct {
        sf::CircleShape shape;
        int speed;
    };
    
    std::vector<StarStruct> circles;
    sf::Vector2u wsize;
    
    bool isOn;
};

#endif
