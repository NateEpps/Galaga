//
// TitlePanel.cpp
// Nathanael Epps
//

#include "TitlePanel.hpp"

#include "Util.hpp"
#include "ControllerPanel.hpp"
#include "Rss/Rss.hpp"

using namespace sf;

TitlePanel::TitlePanel(ControllerPanel* cp)
    : parent(cp), playButton(prototype), quitButton(prototype), copyright(prototype)
{
    auto titleInfo = getResourceTitlePng();
    if (!titleTexture.loadFromMemory(titleInfo.data, titleInfo.size))
        throw MakeException("Could not load title.png");

    titleSprite.emplace(titleTexture);

    Vector2u wsize = GetLastWindow()->getSize();
    titleSprite.value().setPosition(sf::Vector2f(0, wsize.y / 8.0));
    SetSize(titleSprite.value(), titleSprite.value().getGlobalBounds(), wsize.x * 0.45, wsize.y * 0.4);
    Center(titleSprite.value(), wsize);
    
    playButton.setString("Play");
    playButton.setPosition(sf::Vector2f(wsize.x / 2.0, wsize.y * 0.55));
    playButton.setCharacterSize(wsize.x * 0.075);
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
    quitButton.setPosition(sf::Vector2f(wsize.x / 2, 3 * wsize.y / 4.0));
    quitButton.setCharacterSize(wsize.x * 0.075);
    Center(quitButton, wsize);
    quitButton.setAction([](){
        GetLastWindow()->close();
    });
    
    copyright.setString("[c] Nathanael Epps & Namco 2018-19");
    copyright.setCharacterSize(wsize.x * 0.01);
    copyright.setPosition(sf::Vector2f(0, wsize.y - copyright.getGlobalBounds().size.y - 5));
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
    target.draw(titleSprite.value(), states);
    
    target.draw(playButton, states);
    target.draw(quitButton, states);
    target.draw(copyright, states);
}
