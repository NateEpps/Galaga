//
// PausePanel.cpp
// Nathanael Epps
//

#include "PausePanel.hpp"

#include "ControllerPanel.hpp"
#include "Util.hpp"

using namespace sf;

PausePanel::PausePanel(ControllerPanel* pcp,
                       GamePanel* pgp,
                       Stars* ps)
{
    if (!pcp || !pgp || !ps)
        throw MakeException("Nullptr");
    
    parent = pcp;
    pGame = pgp;
    pStars = ps;
    
    auto wsize = GetLastWindow()->getSize();
    
    heading.setFont(prototype);
    heading.setString("Paused");
    heading.setCharacterSize(wsize.x * 0.1);
    heading.setPosition(0, wsize.y * 0.25);
    Center(heading, wsize);
    
    cont.setFont(prototype);
    cont.setString("Continue");
    cont.setCharacterSize(wsize.x * 0.05);
    cont.setPosition(0, wsize.y * 0.5);
    Center(cont, wsize);
    cont.setAction([this](){
        parent->setCurrentPanel(parent->getGamePanel());
    });
    
    exit.setFont(prototype);
    exit.setString("Exit");
    exit.setCharacterSize(cont.getCharacterSize());
    exit.setPosition(0, wsize.y * 0.65);
    Center(exit, wsize);
    exit.setAction([this](){
        parent->setCurrentPanel(parent->getTitlePanel());
    });
}

void PausePanel::process(sf::Event event)
{
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        parent->setCurrentPanel(parent->getGamePanel());
    }
    else {
        cont.process(event);
        exit.process(event);
    }
}

void PausePanel::update(sf::Time dt)
{
    cont.update();
    exit.update();
}

void PausePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*pStars);
    target.draw(*pGame);
    target.draw(heading, states);
    target.draw(cont, states);
    target.draw(exit, states);
}
