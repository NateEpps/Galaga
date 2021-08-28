//
// GamePanel.cpp
// Nathanael Epps
//

#include "GamePanel.hpp"

#include "ControllerPanel.hpp"
#include "Rss/Rss.hpp"
#include "Util.hpp"

using namespace sf;

static Texture heartTexture;

GamePanel::GamePanel(ControllerPanel* pcp) : parent(pcp)
{
    // Only put things here that don't change
    // when the game is re-launched, things that change
    // go in "reset"
    
    static bool init = false;
    if (!init) {
        rss_t heart = getResourceHeartPng();
        if (!heartTexture.loadFromMemory(heart.data, heart.size))
            throw MakeException("Could not load Heart.png");
        init = true;
    }
    
    const sf::Vector2u wsize = GetLastWindow()->getSize();
    
    for (int x = 0; x < 3; x++) {
        sf::Sprite sprite;
        sprite.setTexture(heartTexture);
        
        const double SideLen = wsize.x * 0.04;
        
        SetSize(sprite, sprite.getGlobalBounds(), SideLen, SideLen);
        
        static const double XOffset = wsize.x * 0.007;
        
        sprite.setPosition(x * (SideLen + XOffset) + 5, 5);
        
        hearts.push_back(sprite);
    }
    
    reset();
    
    pointsText.setFont(prototype);
    pointsText.setCharacterSize(wsize.x * 0.0275);
    pointsText.setString("Points: (?)");
}

#ifdef DEBUG

/*virtual*/ GamePanel::~GamePanel()
{
#warning Need this?
}

#endif

void GamePanel::process(sf::Event event)
{
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
        parent->setCurrentPanel(parent->getPausePanel());
    else
        pplayer->process(event);
}

/*private*/
GamePanel::MissileItr GamePanel::testAndRemoveMissiles(MissileItr start, MissileItr end)
{
    return std::remove_if(start, end, [&](const Missile& m){
        return m.getGlobalBounds().intersects(pplayer->getBounds());
    });
}

void GamePanel::update(sf::Time dt)
{
    pplayer->update(dt);
    pgroup->update(dt);
    
    for (Missile& m : extraMissiles)
        m.update(dt);
    
    // test player's missiles against enemies
    if (pplayer->getAmtMissiles() > 0) {
        // friends? hack-ish solution
        auto& missiles = pplayer->missiles;
        auto& enemies = pgroup->sprites;
        
        auto lambda = [&](Enemy& enemy) {
            FloatRect eBounds = enemy.getBounds();
            for (Sprite& missile : missiles) {
                FloatRect mBounds = missile.getGlobalBounds();
                if (eBounds.intersects(mBounds)) {
                    // save missiles from enemies that die mid-fire
#warning This overwrites any existing extra missiles
                    if (enemy.getMissilesRef().size() > 0)
                        std::swap(extraMissiles, enemy.getMissilesRef());
                    
                    enemyIsHit();
                    return true;
                }
            }
            
            return false;
        };
        
        auto eErase = std::remove_if(enemies.begin(), enemies.end(), lambda);
        
        if (eErase != enemies.end())
            missiles.pop_front();
        
        enemies.erase(eErase, enemies.end());
    }
    
    if (pgroup->getAmtEnemies() == 0)
        setupGroup();
    
    if (!pgroup->hasUpdate())
        pgroup->setUpdateMode(UpdateMode::Parade);
    
    // test enemy missiles against player
    for (Enemy& e : *pgroup) {
        auto& missiles = e.getMissilesRef();
        
        auto itr = testAndRemoveMissiles(missiles.begin(), missiles.end());
        if (itr != missiles.end()) {
            missiles.erase(itr, missiles.end());
            playerIsHit();
        }
    }
    
    // test extra missiles (from enemies that died while shooting)
    auto itr = testAndRemoveMissiles(extraMissiles.begin(), extraMissiles.end());
    if (itr != extraMissiles.end()) {
        extraMissiles.erase(itr, extraMissiles.end());
        playerIsHit();
    }
}

void GamePanel::onLoseFocus()
{
    parent->setCurrentPanel(parent->getPausePanel());
}

void GamePanel::reset()
{
    Print("Resetting game panel...");
    
    setupPlayer();
    setupGroup();
    
    lives = 3;
    pointsActual = 0;
    
    static const auto wsize = GetLastWindow()->getSize();
    static const auto Offset = wsize.x * 0.01;
    
    pointsText.setPosition(wsize.x, Offset / 2.0);
    pointsText.setString("Points: " + ToString(pointsActual));
    pointsText.move((-1 * pointsText.getGlobalBounds().width) - Offset, 0);
}

/*private*/ void GamePanel::setupPlayer()
{
    Vector2u wsize = GetLastWindow()->getSize();
    pplayer = std::make_unique<Player>();
    pplayer->setPosition(wsize.x / 2, wsize.y * 0.8);
    pplayer->move(-1 * (pplayer->getBounds().width / 2.0),
                  -1 * (pplayer->getBounds().height / 2.0));
}

/*private*/ void GamePanel::setupGroup()
{
    Vector2u wsize = GetLastWindow()->getSize();
#warning Change these later
    int width = 5;
    int height = 1;

    rss_t textureData = getRandomEnemyPng();
    
    // initialize the group
    pgroup = std::make_unique<EnemyGroup>(this, textureData, width, height);
    
    // start offscreen
    auto enemyBounds = pgroup->getSingleEnemyBounds();
    pgroup->setUpdateMode(UpdateMode::Instant);
    pgroup->stackAt(-1 * enemyBounds.width,
                    -1 * enemyBounds.height);
    
    // set up so it moves onscreen
    Vector2f center(wsize.x / 2, wsize.y * 0.1);
    center.x -= pgroup->getBounds().width / 2;
    
    // Randomly pick update mode
#warning Switch this back eventually
    /*
    if (RandBool() || height == 1)
        pgroup->setUpdateMode(UpdateMode::Concurrent);
    else
        pgroup->setUpdateMode(UpdateMode::Sequential);
     */
    pgroup->setUpdateMode(UpdateMode::Concurrent);
    
    pgroup->addPoint(wsize.x * 0.1, wsize.y * 0.5);
    pgroup->spreadAt(center);
    
    // Remove all extra missiles
    extraMissiles.clear();
}

/*private*/ void GamePanel::enemyIsHit()
{
    // this method handles what happens when
    // enemy is hit, besides removing from relavent
    // containers
    
    pointsActual += 10;
    
    static const auto wsize = GetLastWindow()->getSize();
    static const auto Offset = wsize.x * 0.01;
    
    pointsText.setPosition(wsize.x, Offset / 2.0);
    pointsText.setString("Points: " + ToString(pointsActual));
    pointsText.move((-1 * pointsText.getGlobalBounds().width) - Offset, 0);
}

/*private*/ void GamePanel::playerIsHit()
{
    lives--;
    
    if (lives == 0) {
        parent->getGameOverPanel()->reset();
        parent->setCurrentPanel(parent->getGameOverPanel());
        parent->getBackgroundRef().stop();
    }
}

sf::Vector2f GamePanel::getPlayerPosition() const
{
    auto pos = pplayer->getPosition();
    auto bounds = pplayer->getBounds();
    
    pos.x += bounds.width / 2;
    pos.y += bounds.height / 2;
    
    return pos;
}

void GamePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*pplayer, states);
    
    target.draw(*pgroup, states);
    
    target.draw(pointsText, states);
    
    for (int x = 0; x < lives; x++)
        target.draw(hearts.at(x), states);
    
    for (const Missile& m : extraMissiles)
        target.draw(m, states);
}


/*bool hitPlayer = false;
 
 missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [&](const Missile& m){
 if (m.getGlobalBounds().intersects(pplayer->getBounds())) {
 hitPlayer = true;
 return true;
 }
 
 return false;
 }), missiles.end());
 
 if (hitPlayer)
 playerIsHit();*/

/*bool hitPlayer = false;
 
 extraMissiles.erase(std::remove_if(extraMissiles.begin(), extraMissiles.end(), [&](const Missile& m) {
 if (m.getGlobalBounds().intersects(pplayer->getBounds())) {
 hitPlayer = true;
 return true;
 }
 
 return false;
 }), extraMissiles.end());
 
 if (hitPlayer)
 playerIsHit();*/
