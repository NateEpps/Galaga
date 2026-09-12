//
// ClickText.cpp
// Nathanael Epps
//

#include "ClickText.hpp"

#include "ControllerPanel.hpp"
#include "Util.hpp"

using namespace sf;

ClickText::ClickText(const sf::Font& font) : sf::Text(font)
{
    isHighlighted = false;
}

void ClickText::process(sf::Event e)
{
    const sf::Event::MouseButtonPressed* mouseEv = e.getIf<sf::Event::MouseButtonPressed>();

    if (mouseEv && isHighlighted) {
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
