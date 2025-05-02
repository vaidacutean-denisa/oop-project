#include "Bullet.h"
#include <cmath>

constexpr float pi = 3.1415f;

Bullet::Bullet(const sf::Texture& bulletTexture, float speed_, const sf::Vector2f& direction_, const sf::Vector2f& position_)
        : speed(speed_), direction(direction_), position(position_)  {
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setPosition(position.x, position.y);

    constexpr float scaleX = 0.1f;
    constexpr float scaleY = 0.1f;
    bulletSprite.setScale(scaleX, scaleY);

    const float angle = std::atan2(direction.y, direction.x) * 180.f / pi;
    bulletSprite.setRotation(angle);
}

void Bullet::drawBullet(sf::RenderWindow& window) const {
    window.draw(bulletSprite);
}

void Bullet::updateBullet(float deltaTime) {
    position += direction * speed * deltaTime;                                  // deplasarea glontului de la un frame la altul
    bulletSprite.setPosition(position.x, position.y);
}

bool Bullet::isOutOfBounds(const sf::RenderWindow& window) const {
    float windowHeight = static_cast<float>(window.getSize().y);
    float windowWidth = static_cast<float>(window.getSize().x);

    return position.x < 0 || position.x > windowWidth||
           position.y < 0 || position.y > windowHeight;
}
