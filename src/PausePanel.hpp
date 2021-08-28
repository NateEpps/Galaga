//
// PausePanel.hpp
// Nathanael Epps
//

#ifndef PAUSEPANEL_HPP
#define PAUSEPANEL_HPP

#include <SFML/Graphics.hpp>

#include "BasePanel.hpp"
#include "ClickText.hpp"

class ControllerPanel;
class GamePanel;
class Stars;

class PausePanel : public BasePanel
{
public:
    PausePanel(ControllerPanel*, GamePanel*, Stars*);
    
    virtual void process(sf::Event) override;
    virtual void update(sf::Time) override;
    
    virtual void draw(sf::RenderTarget&,
                      sf::RenderStates) const override;
    
private:
    ControllerPanel* parent;
    GamePanel* pGame;
    Stars* pStars;
    
    sf::Text heading;
    ClickText cont;
    ClickText exit;
};

#endif
