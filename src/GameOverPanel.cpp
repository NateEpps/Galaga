//
// GameOverPanel.cpp
// Nathanael Epps
//

#include "GameOverPanel.hpp"

#include "ControllerPanel.hpp"
#include "StoredData.hpp"
#include "Util.hpp"

GameOverPanel::GameOverPanel(ControllerPanel* pcp)
    : parent(pcp), header(prototype), gameScore(prototype),
      highScore(prototype), mainMenu(prototype), playAgain(prototype)
{
    auto wsize = GetLastWindow()->getSize();
    
    header.setString("Game Over");
    header.setPosition({0, (float)(wsize.y * 0.15)});
    header.setCharacterSize(wsize.x * 0.1);
    Center(header, wsize);
    
    // gameScore set up in reset
    
    playAgain.setString("Play Again");
    playAgain.setPosition({0, (float)(wsize.y * 0.65)});
    playAgain.setCharacterSize(wsize.x * 0.04);
    Center(playAgain, wsize);
    playAgain.setAction([this](){
        parent->getBackgroundRef().restart();
        parent->getGamePanel()->reset();
        parent->setCurrentPanel(parent->getGamePanel());
    });
    
    mainMenu.setString("Main Menu");
    mainMenu.setPosition({0, (float)(playAgain.getPosition().y + playAgain.getGlobalBounds().size.y + (wsize.x * 0.02))});
    mainMenu.setCharacterSize(playAgain.getCharacterSize());
    Center(mainMenu, wsize);
    mainMenu.setAction([this](){
        parent->getBackgroundRef().restart();
        parent->setCurrentPanel(parent->getTitlePanel());
    });
}

GameOverPanel::~GameOverPanel()
{
#warning Todo- store highscore
}

void GameOverPanel::process(sf::Event e)
{
// #define EXIT_ON_ESC
#ifdef EXIT_ON_ESC
    const sf::Event::KeyPressed* keyEv = e.getIf<sf::Event::KeyPressed>();
    if (keyEv && keyEv->code == sf::Keyboard::Key::Escape)
        exit(EXIT_SUCCESS);
#endif

    playAgain.process(e);
    mainMenu.process(e);
}

void GameOverPanel::update(sf::Time dt)
{
    playAgain.update();
    mainMenu.update();
}

void GameOverPanel::reset()
{
    auto wsize = GetLastWindow()->getSize();
    unsigned prevScore = dynamic_cast<GamePanel*>(parent->getGamePanel())->getCurrentPoints();
    
    gameScore.setString("Score: " + ToString(prevScore));
    gameScore.setCharacterSize(wsize.x * 0.03);
    gameScore.setPosition({0, (float)(header.getPosition().y + (header.getGlobalBounds().size.y * 1.4))});
    Center(gameScore, wsize);
    
    unsigned highSc = StoredData::getHighScore();
    if (prevScore > highSc) {
        StoredData::setHighScore(prevScore);
        highScore.setString("NEW High Score: " + ToString(prevScore));
    }
    else {
        highScore.setString("High Score: " + ToString(highSc));
    }
    
    highScore.setCharacterSize(wsize.x * 0.03);
    highScore.setPosition({0, (float)(gameScore.getPosition().y + gameScore.getGlobalBounds().size.y + (wsize.x * 0.02))});
    Center(highScore, wsize);
}

void GameOverPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(header, states);
    target.draw(gameScore, states);
    target.draw(highScore, states);
    
    target.draw(playAgain, states);
    target.draw(mainMenu, states);
}
