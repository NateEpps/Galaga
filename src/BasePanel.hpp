//
// BasePanel.hpp
// Nathanael Epps
//

#ifndef BASEPANEL_HPP
#define BASEPANEL_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>

class BasePanel : public sf::Drawable
{
public:
    BasePanel();
    
    virtual void process(sf::Event) = 0;
    
    virtual void update(sf::Time) = 0;
    
    virtual void onLoseFocus() { };
    virtual void onGainFocus() { };
    
    virtual void reset() { };
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;
    
protected:
    static sf::Font prototype;
};

#endif
