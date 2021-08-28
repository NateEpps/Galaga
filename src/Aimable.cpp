//
// Aimable.cpp
// Nathanael Epps
//

#include "Aimable.hpp"

#include "Util.hpp"

void Aimable::moveTowards(sf::Vector2f target, double factor)
{
    moveAtAngle(GetDirection(getPosition(), target), factor);
}

void Aimable::moveAtAngle(unsigned degrees, double factor)
{
    double radians = (degrees * M_PI) / 180;
    
    double dy = tan(radians);
    double dx = 1;
    
    if (degrees == 0) {
        dy = 0;
        // dx stays 1
    }
    else if (degrees > 0 && degrees < 90) {
        dy = abs(dy);
        dx = abs(dx);
    }
    else if (degrees == 90) {
        dy = 1;
        dx = 0;
    }
    else if (degrees > 90 && degrees < 180) {
        dx = -1 * abs(dx);
        dy = abs(dy);
    }
    else if (degrees == 180) {
        dy = 0;
        dx = -1;
    }
    else if (degrees > 180 && degrees < 270) {
        dx = -1 * abs(dx);
        dy = -1 * abs(dy);
    }
    else if (degrees == 270) {
        dy = -1;
        dx = 0;
    }
    else if (degrees > 270) {
        dx = abs(dx);
        dy = -1 * abs(dy);
    }
    
    move(dx * factor, dy * factor);
}

unsigned GetDirection(sf::Vector2f v1, sf::Vector2f v2)
{
    double alpha = atan(abs(v2.y - v1.y) / abs(v2.x - v1.x));
    double theta;
    
    if (v1.y < v2.y) {
        if (v1.x < v2.x)  // q1
            theta = alpha;
        
        else if (v1.x > v2.x) // q2
            theta = M_PI - alpha;
        
        else // above, on y axis
            theta = M_PI / 2;
    }
    else if (v1.y > v2.y) {
        if (v1.x < v2.x) // q4
            theta = (2 * M_PI) - alpha;
        
        else if (v1.x > v2.x) // q3
            theta = ((3 * M_PI) / 2) - alpha;
        
        else // below, on y axis
            theta = ((3 * M_PI) / 2);
    }
    else { // on the x axis
        if (v1.x < v2.x)
            theta = 0.0;
        
        else if (v1.x > v2.x) // 180 degrees
            theta = M_PI;
        
        else // points are the same
            throw MakeException("Points are the same");
    }
    
    // return radians --> degrees
    return round((theta * 180) / M_PI);
}

double AngleToSlope(unsigned degrees)
{
    double radians = (degrees * M_PI) / 180.0;
    
    return abs(tan(radians));
}
