//
// GamePanel.hpp
// Nathanael Epps
//

#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "BasePanel.hpp"
#include "Player.hpp"
#include "EnemyGroup.hpp"

class ControllerPanel;

class GamePanel : public BasePanel
{
public:
    explicit GamePanel(ControllerPanel*);
#ifdef DEBUG
    virtual ~GamePanel();
#endif
    virtual void process(sf::Event) override;
    virtual void update(sf::Time) override;
    
    virtual void onLoseFocus() override;
    
    virtual void reset() override;
    
    sf::Vector2f getPlayerPosition() const;
    
    virtual void draw(sf::RenderTarget&,
                      sf::RenderStates) const override;
    
    inline unsigned getCurrentPoints() const { return pointsActual; }
    
private:
    void setupPlayer();
    void setupGroup();
    
    void enemyIsHit();
    void playerIsHit();
    
    typedef std::deque<Missile>::iterator MissileItr;
    
    MissileItr testAndRemoveMissiles(MissileItr, MissileItr);
    
    ControllerPanel* parent;
    
    std::unique_ptr<Player> pplayer;
    
    std::unique_ptr<EnemyGroup> pgroup;
    
    std::vector<sf::Sprite> hearts;
    unsigned lives;
    
    std::deque<Missile> extraMissiles;
    
    sf::Text pointsText;
    unsigned pointsActual;
};

#endif
