//
// ClickText.cpp
// Nathanael Epps
//

#include "ClickText.hpp"

#include "ControllerPanel.hpp"
#include "Util.hpp"

using namespace sf;

ClickText::ClickText()
{
    isHighlighted = false;
}

void ClickText::process(sf::Event e)
{
    if (e.type == Event::MouseButtonPressed && isHighlighted) {
        Vector2f mousePos = (Vector2f) Mouse::getPosition(*GetLastWindow());
        
        if (getGlobalBounds().contains(mousePos))
            mAction();
    }
}

void ClickText::update()
{
    Vector2f mousePos = (Vector2f) Mouse::getPosition(*GetLastWindow());
    FloatRect bounds = getGlobalBounds();
    
    if (!isHighlighted && bounds.contains(mousePos)) {
        setFillColor(Color::Cyan);
        isHighlighted = true;
    }
    else if (isHighlighted && !bounds.contains(mousePos)) {
        setFillColor(Color::White);
        isHighlighted = false;
    }
}
