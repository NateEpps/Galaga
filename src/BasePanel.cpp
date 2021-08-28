//
// BasePanel.cpp
// Nathanael Epps
//

#include "BasePanel.hpp"

#include "Rss/Rss.hpp"
#include "Util.hpp"

using namespace sf;

static bool fontInit = false;

Font BasePanel::prototype;

BasePanel::BasePanel()
{
    if (!fontInit) {
        rss_t font = getResourcePrototypeTtf();
        if (!prototype.loadFromMemory(font.data, font.size))
            throw MakeException("Could not load font");
        
        fontInit = true;
    }
}
