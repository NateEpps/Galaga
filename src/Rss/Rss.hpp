//
// Rss.hpp
// Nathanael Epps
//

#ifndef RSS_HPP
#define RSS_HPP

#include <ostream>

struct rss_t {
    void* data;
    size_t size;
};

std::ostream& operator<<(std::ostream&, const rss_t&);

/* Pictures */
rss_t getResourceBeePng();
rss_t getResourceEnemyMissilePng();
rss_t getResourceHeartPng();
rss_t getResourcePlayerMissilePng();
rss_t getResourcePurplePng();
rss_t getResourceShipPng();
rss_t getResourceTitlePng();
rss_t getResourceYellowPng();

/* Font */
rss_t getResourcePrototypeTtf();

/* Convenience */
rss_t getRandomEnemyPng();

#endif
