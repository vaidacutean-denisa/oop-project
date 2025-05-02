#include "Enemy.h"

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Enemy - health = " << enemy.health << '\n'
       << "Speed = " << enemy.speed << '\n';
    return os;
}
Enemy::Enemy(float health_, float speed_, const sf::Vector2f& position_) //, const sf::Texture& texture_)
    : health(health_), speed(speed_), position(position_) // enemyTexture(texture_)
{
    // enemySprite.setTexture(texture_);
    // enemySprite.setPosition(position_);
}

Enemy::Enemy(const Enemy& other) : health(other.health), speed(other.speed), position(other.position){ // enemyTexture(other.enemyTexture) {
    std::cout << "cc Enemy\n";
    // enemySprite.setPosition(position);
    // enemySprite.setTexture(enemyTexture);
}

Enemy& Enemy::operator=(const Enemy& other) {
    std::cout << "replicating enemies.. a true test of my patience (op=)\n";
    if (this != &other) {
        health = other.health;
        speed = other.speed;
        position = other.position;
        //
        // enemySprite.setPosition(position);
        // enemySprite.setTexture(enemyTexture);
    }
    return *this;
}

Enemy::~Enemy() {
    std::cout << "One step closer to survival.. (destructor enemy)\n";
}

// void Enemy::drawEnemies(sf::RenderWindow& window) const {
//     window.draw(enemySprite);
// }
//