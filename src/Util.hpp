//
// Util.hpp
// Nathanael Epps
//

#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdexcept>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Print.hpp"

using std::string;

void PrintInfo();

typedef sf::Uint32 mask_t;
void GetVideoMode(sf::VideoMode&, mask_t&, bool);

void SetLastWindow(sf::RenderWindow*);
sf::RenderWindow* GetLastWindow();

int RandInt(int, int);

bool IsClose(float, float, float t = 0.001);
bool IsClose(sf::Vector2f, sf::Vector2f, float t = 0.001);

void OffscreenGuard(sf::Transformable&, sf::Vector2f);

#define RandBool() (RandInt(0, 1) == 0)

#define Round(f) ((int) f + 0.5)

////////////////////////////////////////////////////////////////////////////////

template <class T>
std::string ToString(const T& t) {
    std::stringstream ss;
    return dynamic_cast<std::stringstream&>(ss << t).str();
}

template <class Scalable>
void SetSize(Scalable& sc, sf::FloatRect csize, float tx, float ty) {
    // auto csize = sc.getGlobalBounds();
    float cx = csize.width;
    float cy = csize.height;
    
    sc.scale(tx / cx, ty / cy);
}

template <class Moveable>
void Center(Moveable& mv, sf::Vector2u bounds) {
    mv.setPosition(bounds.x / 2.0, mv.getPosition().y);
    mv.move(-1 * (mv.getGlobalBounds().width / 2.0), 0);
}

/*template <class Dest, class From>
Dest lexical_cast(const From& f) {
    std::stringstream ss;
    ss << f;
    
    Dest d;
    ss >> d;
    
    return d;
}*/

////////////////////////////////////////////////////////////////////////////////

#define GetFuncName() std::string(__PRETTY_FUNCTION__)

#define MakeException(mssg) (std::runtime_error(GetFuncName() + ":" + ToString(__LINE__) + ": " + mssg))

#endif
