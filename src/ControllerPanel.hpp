//
// ControllerPanel.hpp
// Nathanael Epps
//

#ifndef CONTROLLERPANEL_HPP
#define CONTROLLERPANEL_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "BasePanel.hpp"
#include "GameOverPanel.hpp"
#include "GamePanel.hpp"
#include "PausePanel.hpp"
#include "Stars.hpp"
#include "TitlePanel.hpp"

class ControllerPanel : public sf::Drawable
{
public:
    ControllerPanel();
    
    void process(sf::Event);
    
    void update(sf::Time);
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    inline BasePanel* getTitlePanel() { return &titlePanel; }
    inline BasePanel* getGamePanel() { return &gamePanel; }
    inline BasePanel* getPausePanel() { return &pausePanel; }
    inline BasePanel* getGameOverPanel() { return &gameOverPanel; }
    
    inline void setCurrentPanel(BasePanel* pbp) { pcurrent = pbp; }
    
    inline Stars& getBackgroundRef() { return background; }
    
private:
    Stars background;
    
    BasePanel* pcurrent;
    TitlePanel titlePanel;
    GamePanel gamePanel;
    PausePanel pausePanel;
    GameOverPanel gameOverPanel;
};

#endif
