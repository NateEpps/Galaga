//
// Print.hpp
// Nathanael Epps
//

#ifndef PRINT
#define PRINT

#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace impl {
    template <class T>
    inline std::ostream& operator<<(std::ostream& stream, sf::Vector2<T> v) {
        return stream << "(" << v.x << ", " << v.y << ")";
    }
    
    template <class T>
    inline void print(std::ostream& stream, const T& t) {
        stream << t;
    }
    
    template <class T, class... Pack>
    void print(std::ostream& stream, const T& t, const Pack&... args) {
        stream << t;
        print(stream, args...);
    }
}

#define Error(...) impl::print(std::cerr, "(Error) ", __PRETTY_FUNCTION__, ":", __LINE__, ":\n\t", __VA_ARGS__, "\n\n")

#ifdef DEBUG

#define Print(...) impl::print(std::cout, __PRETTY_FUNCTION__, ":", __LINE__, ":\n\t", __VA_ARGS__, "\n")

#else
# define Print(...) 
#endif

#endif
