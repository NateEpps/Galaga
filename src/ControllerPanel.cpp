//
// ConrollerPanel.cpp
// Nathanael Epps
//

#include "ControllerPanel.hpp"

#include "Util.hpp"

using namespace sf;

static const int AmtOfStars = 500;

ControllerPanel::ControllerPanel() :

background(AmtOfStars),
titlePanel(this),
gamePanel(this),
pausePanel(this, &gamePanel, &background),
gameOverPanel(this)

{
    pcurrent = &titlePanel;
    
    titlePanel.onGainFocus();
}

void ControllerPanel::process(sf::Event event)
{
    if (event.type == Event::LostFocus)
        pcurrent->onLoseFocus();
    else if (event.type == Event::GainedFocus)
        pcurrent->onGainFocus();
    else
        pcurrent->process(event);
}

void ControllerPanel::update(sf::Time delta)
{
    if (pcurrent != &pausePanel) // hack-ish, but...
        background.update(delta);
    
    pcurrent->update(delta);
}

void ControllerPanel::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const
{
    if (pcurrent != &pausePanel)
        target.draw(background, states);
    
    target.draw(*pcurrent, states);
}
