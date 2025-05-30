#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
    float speed;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Sprite bulletSprite;

public:
    // constructor
    Bullet(const sf::Texture& bulletTexture, float speed_, const sf::Vector2f& direction_, const sf::Vector2f& position_);

    // methods
    void drawBullet(sf::RenderWindow& window) const;
    void updateBullet(float deltaTime);
    bool isOutOfBounds(const sf::RenderWindow& window) const;

    // getters & setters
    sf::FloatRect getBounds() const;
};

#endif //BULLET_H
