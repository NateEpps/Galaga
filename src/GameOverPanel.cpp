//
// GameOverPanel.cpp
// Nathanael Epps
//

#include "GameOverPanel.hpp"

#include "ControllerPanel.hpp"
#include "StoredData.hpp"
#include "Util.hpp"

GameOverPanel::GameOverPanel(ControllerPanel* pcp) : parent(pcp)
{
    auto wsize = GetLastWindow()->getSize();
    
    header.setString("Game Over");
    header.setPosition(0, wsize.y * 0.15);
    header.setCharacterSize(wsize.x * 0.1);
    header.setFont(prototype);
    Center(header, wsize);
    
    // gameScore set up in reset
    
    playAgain.setString("Play Again");
    playAgain.setPosition(0, wsize.y * 0.65);
    playAgain.setCharacterSize(wsize.x * 0.04);
    playAgain.setFont(prototype);
    Center(playAgain, wsize);
    playAgain.setAction([this](){
        parent->getBackgroundRef().restart();
        parent->getGamePanel()->reset();
        parent->setCurrentPanel(parent->getGamePanel());
    });
    
    mainMenu.setString("Main Menu");
    mainMenu.setPosition(0, playAgain.getPosition().y + playAgain.getGlobalBounds().height + (wsize.x * 0.02));
    mainMenu.setCharacterSize(playAgain.getCharacterSize());
    mainMenu.setFont(prototype);
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
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
        exit(EXIT_SUCCESS);
    
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
    gameScore.setPosition(0, header.getPosition().y + (header.getGlobalBounds().height * 1.4));
    gameScore.setFont(prototype);
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
    highScore.setPosition(0, gameScore.getPosition().y + gameScore.getGlobalBounds().height + (wsize.x * 0.02));
    highScore.setFont(prototype);
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
