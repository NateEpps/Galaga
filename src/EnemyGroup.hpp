//
// EnemyGroup.hpp
// Nathanael Epps
//

#ifndef ENEMYGROUP_HPP
#define ENEMYGROUP_HPP

#include <ostream>
#include <vector>
#include <deque>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Enemy.hpp"
#include "Rss/Rss.hpp"

enum class UpdateMode {
    Sequential, Concurrent, Instant, Parade
};

std::ostream& operator<<(std::ostream&, UpdateMode);

class GamePanel;

class EnemyGroup : public sf::Drawable
{
public:
    /* Construct / destruct */
    EnemyGroup(GamePanel*, rss_t, size_t, size_t);
    EnemyGroup(const EnemyGroup&) = delete;
    EnemyGroup(EnemyGroup&&) = delete;

    /* Integrate with superclass */
    void update(sf::Time);
    
    bool hasUpdate() const;
    
    /* Position + layout */
    void spreadAt(float, float);
    void stackAt(float, float);
    
    void addPoint(float, float);
    
    void clearAllPoints();
    
    void setUpdateMode(UpdateMode);
    
    /* Utility get stuff */
    sf::FloatRect getBounds() const;
    
    sf::FloatRect getSingleEnemyBounds() const;
    
    std::vector<sf::FloatRect> getListOfGlobalBounds() const;
    
    /* Drawble */
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    ////////////////////////////////////////////////////////////////////////////////
    
    /* Make it iterable */
    typedef std::deque<Enemy>::iterator iterator;
    typedef std::deque<Enemy>::const_iterator const_iterator;
    
    inline iterator begin() { return sprites.begin(); }
    inline iterator end() { return sprites.end(); }
    
    inline const_iterator begin() const { return sprites.begin(); }
    inline const_iterator end() const { return sprites.end(); }
    
    inline Enemy& getFront() { return sprites.front(); }
    inline const Enemy& getFront() const { return sprites.front(); }
    
    ////////////////////////////////////////////////////////////////////////////////
    
    /* Convenience overloads */
    inline void spreadAt(sf::Vector2f v) { spreadAt(v.x, v.y); }
    inline void stackAt(sf::Vector2f v) { stackAt(v.x, v.y); }
    
    inline void addPoint(sf::Vector2f v) { addPoint(v.x, v.y); }
    
    /* More inline stuff */
    inline size_t getAmtEnemies() const { return sprites.size(); }
    
    ////////////////////////////////////////////////////////////////////////////////
    
    friend class GamePanel;
    
protected:
    /* Retrieving enemies */
    inline Enemy& get(int x, int y) { return sprites.at(x * height + y); }
    
private:
    GamePanel* parent;
    sf::Texture texture;
    size_t width, height;
    UpdateMode updateMode;
    std::deque<Enemy> sprites;
    Enemy* pcurrent;
    float lowy;
    
    static float Offset;
    static float leftx, rightx;
};

rss_t GetRandomEnemyData();

#endif
