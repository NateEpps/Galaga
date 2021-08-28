//
// GameOverPanel.hpp
// Nathanael Epps
//

#ifndef GAMEOVERPANEL
#define GAMEOVERPANEL

#include "BasePanel.hpp"
#include "ClickText.hpp"
#include <SFML/Graphics.hpp>

class ControllerPanel;

class GameOverPanel : public BasePanel
{
public:
    GameOverPanel(ControllerPanel*);
    virtual ~GameOverPanel();
    
    virtual void process(sf::Event) override;
    
    virtual void update(sf::Time) override;
    
    virtual void onLoseFocus() override { };
    virtual void onGainFocus() override { };
    
    virtual void reset() override;
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    ControllerPanel* parent;
    
    sf::Text header;
    sf::Text gameScore;
    sf::Text highScore;
    ClickText playAgain;
    ClickText mainMenu;
};

#endif
