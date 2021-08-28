//
// Stars.cpp
// Nathanael Epps
//

#include "Stars.hpp"

#include "Util.hpp"

using namespace sf;

static const Color StarColor = Color(150, 255, 255);
static const double SizePercent = 0.0015;
static const int Offset = 5;

static const int LowSpeed = 50;
static const int HighSpeed = 125;

Stars::Stars(const int amt) : wsize(GetLastWindow()->getSize())
{
    for (int x = 0; x < amt; x++) {
        CircleShape theCircle;
        
        theCircle.setFillColor(StarColor);
        theCircle.setRadius(wsize.y * SizePercent);
        theCircle.setPosition(RandInt(Offset, wsize.x - Offset),
#ifdef START_AT_TOP
                              RandInt(-100, 0));
#else
                              RandInt(Offset, wsize.y - Offset));
#endif
        
        circles.push_back({theCircle, RandInt(LowSpeed, HighSpeed)});
    }
    
    isOn = true;
}

void Stars::update(sf::Time dt)
{
    if (isOn) {
        for (StarStruct& ss : circles) {
            ss.shape.move(0, ss.speed * dt.asSeconds());
            if (ss.shape.getPosition().y > wsize.y + 20)
                ss.shape.setPosition(ss.shape.getPosition().x, -50);
        }
    }
    else {
        for (StarStruct& ss : circles) {
            if (ss.shape.getPosition().y <= wsize.y + 20)
                ss.shape.move(0, ss.speed * dt.asSeconds());
        }
    }
}

void Stars::restart()
{
    isOn = true;
    
    for (StarStruct& ss : circles) {
        ss.shape.setPosition(RandInt(Offset, wsize.x - Offset),
#ifdef START_AT_TOP
                             RandInt(-100, 0));
#else
                             RandInt(Offset, wsize.y - Offset));
#endif
    }
}

void Stars::draw(sf::RenderTarget& target,
                 sf::RenderStates states) const
{
    for (const StarStruct& ss : circles)
        target.draw(ss.shape, states);
}
