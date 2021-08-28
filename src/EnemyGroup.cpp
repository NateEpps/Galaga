//
// EnemyGroup.cpp
// Nathanael Epps
//

#include "EnemyGroup.hpp"
#include "GamePanel.hpp"
#include "Util.hpp"

using namespace sf;

std::ostream& operator<<(std::ostream& stream, UpdateMode mode)
{
    switch (mode)
    {
        case UpdateMode::Sequential: stream << "UpdateMode::Sequential"; break;
        case UpdateMode::Concurrent: stream << "UpdateMode::Concurrent"; break;
        case UpdateMode::Instant: stream << "UpdateMode::Instant"; break;
        case UpdateMode::Parade: stream << "UpdateMode::Parade"; break;
        default: throw MakeException("Invalid UpdateMode");
    }
    
    return stream;
}

/*
 sf::Texture texture;
 size_t width, height;
 UpdateMode updateMode;
 std::deque<Enemy> sprites;
 Enemy* pcurrent;
 float lowy;
 
 static float Offset;
 static float leftx, rightx;
 */

float EnemyGroup::Offset = -1;
float EnemyGroup::leftx = -1;
float EnemyGroup::rightx = -1;

EnemyGroup::EnemyGroup(GamePanel* p, rss_t resource, size_t x, size_t y) : parent(p)
{
    if (x == 0 || y == 0)
        throw MakeException("x and y must be >0");
    
    if (!texture.loadFromMemory(resource.data, resource.size))
        throw MakeException("Couldn't load texture");
    
    width = x;
    height = y;
    
    updateMode = UpdateMode::Concurrent;
    
    if (IsClose(Offset, -1))
        Offset = GetLastWindow()->getSize().x * 0.02;
    
    for (int i = 0; i < x * y; i++) {
        sprites.emplace_back(texture);
        sprites.back().setPosition(0, 0);
    }
    
    pcurrent = nullptr;
    
    lowy = -1;
    
    if (leftx < 0) // hasn't been set up yet
    {
        static Vector2u wsize = GetLastWindow()->getSize();
        
        leftx = wsize.x * 0.15;
        rightx = wsize.x * 0.85;
    }
}

void EnemyGroup::update(sf::Time dt)
{
    static const Vector2u wsize = GetLastWindow()->getSize();
    
    if (updateMode == UpdateMode::Parade) {
        // set up current sprite to parade
        if (pcurrent == nullptr && sprites.size() > 0) {
            pcurrent = &sprites.front();
            
            if (lowy < 0) {
                FloatRect bounds = getBounds();
                
                lowy = bounds.top + bounds.height + Offset;
            }
        
            if (pcurrent->getPosition().x >= (wsize.x / 2.0))
                pcurrent->addPoint(rightx, lowy);
            
            pcurrent->setSpeedFactor(1.5);
            
            pcurrent->addPoint(leftx, lowy);
            pcurrent->addPoint(rightx, lowy);
            
            pcurrent->addPoint(wsize.x * 1.1, wsize.y * 0.67);
        }
        
        // parade current sprite
        if (pcurrent != nullptr) {
            pcurrent->update(dt);
            
#warning Make this more sophisticated
            //Print("Parading...");
            // Shoot at Galaga
            if (IsClose(pcurrent->getPosition().x, wsize.x / 2, wsize.x * 0.02)) {
                //Print("Firing...");
                pcurrent->fireAt(parent->getPlayerPosition());
            }
            
            // if current sprite is done...
            if (!pcurrent->hasPoints()) {
                sprites.pop_front();
                pcurrent = nullptr;
            }
        }
    }
    else {
        for (Enemy& enemy : *this) {
            if (enemy.hasPoints()) {
                if (updateMode == UpdateMode::Sequential ||
                    updateMode == UpdateMode::Concurrent)
                {
                    enemy.update(dt);
                    
                    if (updateMode == UpdateMode::Sequential)
                        break;
                }
                else // Instant
                {
                    enemy.setPosition(enemy.getCurrentPoint());
                    enemy.pop();
                }
            }
        }
    }
}

bool EnemyGroup::hasUpdate() const
{
    for (const Enemy& en : *this)
        if (en.hasPoints())
            return true;
    
    return false;
}

void EnemyGroup::spreadAt(float px, float py)
{
    Vector2f curPos(px, py);
    auto bounds = sprites.at(0).getBounds();
    
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            get(x, y).addPoint(curPos);
            
            curPos.x += bounds.width + Offset;
        }
        
        curPos.x = px;
        curPos.y += bounds.height + Offset;
    }
}

void EnemyGroup::stackAt(float px, float py)
{
    for (Enemy& enemy : *this)
        enemy.setPosition(px, py);
}

void EnemyGroup::addPoint(float px, float py)
{
    for (Enemy& enemy : *this)
        enemy.addPoint(px, py);
}

void EnemyGroup::clearAllPoints()
{
    for (Enemy& enemy : *this)
        enemy.clearPoints();
}

void EnemyGroup::setUpdateMode(UpdateMode um)
{
    updateMode = um;
}

FloatRect EnemyGroup::getBounds() const
{
    if (sprites.empty())
        throw MakeException("Cannot get bounds of empty EnemyGroup");
    
    FloatRect spriteBounds = sprites.front().getBounds();
    
    float px = sprites.front().getPosition().x;
    float py = sprites.front().getPosition().y;
    
    // Offset-x and offset-y, maybe?
    float sx = (spriteBounds.width * width) + (Offset * (width - 1));
    float sy = (spriteBounds.height * height) + (Offset * (height - 1));
    
    return FloatRect(px, py, sx, sy);
}

FloatRect EnemyGroup::getSingleEnemyBounds() const
{
    if (sprites.empty())
        throw MakeException("Cannot get bounds of empty EnemyGroup");
    
    return sprites.front().getBounds();
}

std::vector<FloatRect> EnemyGroup::getListOfGlobalBounds() const
{
    std::vector<FloatRect> vec;
    for (const Enemy& en : *this)
        vec.push_back(en.getBounds());
    
    return vec;
}

void EnemyGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Enemy& enemy : *this)
        target.draw(enemy, states);
}
