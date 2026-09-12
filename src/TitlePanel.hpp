//
// TitlePanel.hpp
// Nathanael Epps
//

#ifndef TITLEPANEL_HPP
#define TITLEPANEL_HPP

#include <optional>

#include <SFML/Graphics/Sprite.hpp>

#include "BasePanel.hpp"
#include "ClickText.hpp"

class ControllerPanel;

class TitlePanel : public BasePanel
{
public:
    explicit TitlePanel(ControllerPanel*);
    
    virtual void process(sf::Event) override;
    virtual void update(sf::Time) override;
    
    virtual void reset() override { };
    
    virtual void draw(sf::RenderTarget&,
                      sf::RenderStates) const override;
    
private:
    ControllerPanel* parent;
    sf::Texture titleTexture;
    std::optional<sf::Sprite> titleSprite;
    
    ClickText playButton;
    ClickText quitButton;
    sf::Text copyright;
};

#endif
