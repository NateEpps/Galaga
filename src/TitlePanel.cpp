//
// TitlePanel.cpp
// Nathanael Epps
//

#include "TitlePanel.hpp"

#include "Util.hpp"
#include "ControllerPanel.hpp"
#include "Rss/Rss.hpp"

using namespace sf;

TitlePanel::TitlePanel(ControllerPanel* cp) : parent(cp)
{
    auto titleInfo = getResourceTitlePng();
    if (!titleTexture.loadFromMemory(titleInfo.data, titleInfo.size))
        throw MakeException("Could not load title.png");
    
    titleSprite.setTexture(titleTexture);
    
    Vector2u wsize = GetLastWindow()->getSize();
    titleSprite.setPosition(0, wsize.y / 8.0);
    SetSize(titleSprite, titleSprite.getGlobalBounds(), wsize.x * 0.45, wsize.y * 0.4);
    Center(titleSprite, wsize);
    
    playButton.setString("Play");
    playButton.setPosition(wsize.x / 2.0, wsize.y * 0.55);
    playButton.setCharacterSize(wsize.x * 0.075);
    playButton.setFont(prototype);
    Center(playButton, wsize);
    playButton.setAction([this](){
//#define TEST_GAMEOVER
#ifndef TEST_GAMEOVER
        parent->setCurrentPanel(parent->getGamePanel());
        parent->getGamePanel()->reset();
#else
        parent->getBackgroundRef().stop();
        parent->setCurrentPanel(parent->getGameOverPanel());
#endif
    });
    
    quitButton.setString("Quit");
    quitButton.setPosition(wsize.x / 2, 3 * wsize.y / 4.0);
    quitButton.setCharacterSize(wsize.x * 0.075);
    quitButton.setFont(prototype);
    Center(quitButton, wsize);
    quitButton.setAction([](){
        GetLastWindow()->close();
    });
    
    copyright.setString("[c] Nathanael Epps & Namco 2018-19");
    copyright.setFont(prototype);
    copyright.setCharacterSize(wsize.x * 0.01);
    copyright.setPosition(0, wsize.y - copyright.getGlobalBounds().height - 5);
    Center(copyright, wsize);
}

void TitlePanel::process(sf::Event event)
{
    playButton.process(event);
    quitButton.process(event);
}

void TitlePanel::update(sf::Time dt)
{
    (void) dt;
    
    playButton.update();
    quitButton.update();
}

void TitlePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(titleSprite, states);
    
    target.draw(playButton, states);
    target.draw(quitButton, states);
    target.draw(copyright, states);
}
