//
// ClickText.hpp
// Nathanael Epps
//

#ifndef CLICKTEXT_HPP
#define CLICKTEXT_HPP

#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

typedef std::function<void(void)> Action;

class ClickText : public sf::Text
{
public:
    ClickText();
    
    void process(sf::Event);
    
    void update();
    
    inline void setAction(Action a) { mAction = a; }
    
private:
    Action mAction;
    bool isHighlighted;
};

#endif
