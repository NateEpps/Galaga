//
// Rss.cpp
// Nathanael Epps
//

#include "Rss.hpp"

#include <cstdlib>
#include <stdexcept>

using namespace std;

ostream& operator<<(ostream& stream, const rss_t& r)
{
    return stream << "(" << r.size << " bytes at " << r.data << ")";
}

rss_t getRandomEnemyPng()
{
    switch (rand() % 3)
    {
        case 0: return getResourceBeePng();
        case 1: return getResourcePurplePng();
        default: return getResourceYellowPng();
    }
}
