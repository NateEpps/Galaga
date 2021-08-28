//
// main.cpp
// Nathanael Epps
//

#include <vector>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Config.hpp>

#include "ControllerPanel.hpp"
#include "Rss/Rss.hpp"
#include "StoredData.hpp"
#include "Util.hpp"

using std::string;
using namespace sf;

static void AddIcon(Window& window)
{
    rss_t bytes = getResourceShipPng();
    
    Image img;
    if (!img.loadFromMemory(bytes.data, bytes.size))
        throw MakeException("Could not load icon");
    
    window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
    // Image is copied, no need to store externally
}

static void help(string cmd)
{
    std::cerr << "Usage: " << cmd << " [options...]\n\n";
    
    std::cerr << "    --window        Force the game to run in a window instead of fullscreen.\n";
    std::cerr << "    --help          Display this help information and exit.\n\n";
    
    exit(EXIT_SUCCESS);
}

static int main2(std::vector<string> args)
{
    if (args.empty())
        throw MakeException("Empty arguments");
    
    if (std::find(args.begin(), args.end(), "--help") != args.end())
        help(args.at(0));
    
    // open stored data
    StoredData sd;
    
    // open the window
    RenderWindow window;
    
    VideoMode vmode;
    mask_t styleMask;
    bool fscreen = (std::find(args.begin(), args.end(), "--window") == args.end());
    
    GetVideoMode(vmode, styleMask, fscreen);
    
    window.create(vmode, "Galaga v" + ToString(GALAGA_VERSION), styleMask);
    SetLastWindow(&window);
    
    Print("Window Size: ", window.getSize());
    
    AddIcon(window);
    
    ControllerPanel panel;
    Event event;
    Clock clock;
    
    Print("Entering game loop");
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else
                panel.process(event);
        }
        
#warning Todo(3) - fixed frame rate?
        panel.update(clock.restart());
        
        window.clear();
        window.draw(panel);
        window.display();
    }
    
    Print("Exit Success!");
    return EXIT_SUCCESS;
}

static const char* ErrPrompt = "Exception: ";

#define CATCH_EXCEPTIONS

int main(int c, const char** v)
{
    PrintInfo();
#ifdef CATCH_EXCEPTIONS
    try {
        std::vector<string> args(v, v + c);
        
        return main2(args);
    }
    catch (std::exception& ex) {
        Error(ErrPrompt, ex.what());
        
        return EXIT_FAILURE;
    }
    catch (...) {
        Error(ErrPrompt, "Unknown!");
        
        return EXIT_FAILURE;
    }
    
    // should be dead code
    return EXIT_FAILURE;
#else
    std::vector<string> args(v, v + c);
    
    return main2(args);
#endif
}
