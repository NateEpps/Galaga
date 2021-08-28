//
// Aimable.hpp
// Nathanael Epps
//

#ifndef AIMABLE_HPP
#define AIMABLE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Aimable
{
public:
    void moveTowards(sf::Vector2f, double);
    
    void moveAtAngle(unsigned, double);
    
    virtual void move(double, double) = 0;
    virtual sf::Vector2f getPosition() const = 0;
};

unsigned GetDirection(sf::Vector2f, sf::Vector2f);

double AngleToSlope(unsigned);

#endif
