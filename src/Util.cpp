//
// Util.cpp
// Nathanael Epps
//

#include "Util.hpp"

#include <Config.hpp>

#include <fstream>

static void PrintInfoToStream(std::ostream& stream)
{
    stream << "Galaga v" << GALAGA_VERSION << ", (c) Nathanael Epps 2018-2019\n";
    
    stream << "Compiled...\n\ton " << __DATE__ << " at " << __TIME__ << "\n";
    
    stream << "\tby " << CMAKE_CXX_COMPILER << "\n";
    
    stream << "\tfor system " << CMAKE_SYSTEM << "\n";
    
    stream << "SFML v" << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR;
    stream << "." << SFML_VERSION_PATCH << "\n";
    
    stream << "CMake v" << CMAKE_VERSION << "\n";
    stream << "C++" << CMAKE_CXX_STANDARD << "\n\n";
}

void PrintInfo()
{
#ifdef DEBUG
    PrintInfoToStream(std::cout);
#endif
    std::fstream stream;
    string fname = CMAKE_BINARY_DIR + "/config.txt";
    
    stream.open(fname, std::ios::out|std::ios::trunc);
    
    if (!stream.is_open())
        throw MakeException("Could not create " + fname);
    
    PrintInfoToStream(stream);
}

////////////////////////////////////////////////////////////////////////////////////////////

void GetVideoMode(sf::VideoMode& vmref, mask_t& maskref, bool fscreen)
{
#ifdef DEBUG
    Print("Selecting ", (fscreen)?("fullscreen"):("windowed"), " mode...");
#endif
    using namespace sf;
    
    auto desk = VideoMode::getDesktopMode();
    
    if (!fscreen) {
        maskref = Style::Default;
        vmref = desk;
        return;
    }
    
    const auto& modes = VideoMode::getFullscreenModes();
    
    auto itr = std::find_if(modes.begin(), modes.end(), [=](VideoMode vm){
        return ((vm.width <= desk.width) &&
                (vm.height <= desk.height) &&
                (vm.bitsPerPixel <= vm.bitsPerPixel));
    });
    
    if (itr != modes.end() && itr->isValid())
    {
        vmref = *itr;
        maskref = Style::Fullscreen;
    }
    else
    {
        Error("Can't create fullscreen, using desktop mode...");
        
        vmref = desk;
        maskref = Style::Default;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

static sf::RenderWindow* pLast = nullptr;

void SetLastWindow(sf::RenderWindow* prw)
{
    pLast = prw;
}

#warning Todo- cache window size instead

sf::RenderWindow* GetLastWindow()
{
    if (pLast == nullptr)
        throw MakeException("NullPointerException");
    else
        return pLast;
}

////////////////////////////////////////////////////////////////////////////////////////////

int RandInt(int lo, int hi)
{
    // Seed the generator
    static bool init = false;
    if (!init) {
#ifdef DEBUG
        auto seed = time(nullptr);
        Print("Using seed: ", seed);
        srand(seed);
#else
        srand(time(nullptr));
#endif
        init = true;
    }
    
    // error checking
    if (lo >= hi)
        throw MakeException("Invalid Range: (" + ToString(lo) + ", " + ToString(hi) + ")");
    else
        // actual number generation
        return (rand() % (hi - lo + 1)) + lo;
}

////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>

bool IsClose(float a, float b, float t)
{
    return fabs(a - b) < t;
}

bool IsClose(sf::Vector2f a, sf::Vector2f b, float t)
{
    return IsClose(a.x, b.x, t) && IsClose(a.y, b.y, t);
}

////////////////////////////////////////////////////////////////////////////////////////////

void OffscreenGuard(sf::Transformable& t, sf::Vector2f shsize)
{
    sf::Vector2u wsize = GetLastWindow()->getSize();
    
    if (t.getPosition().x < 0)
        t.setPosition(1, t.getPosition().y);
    if (t.getPosition().x > wsize.x - shsize.x)
        t.setPosition(wsize.x - shsize.x - 1, t.getPosition().y);
    
    if (t.getPosition().y < 0)
        t.setPosition(t.getPosition().x, 1);
    if (t.getPosition().y > wsize.y - shsize.y)
        t.setPosition(t.getPosition().x, wsize.y - shsize.y - 1);
}
