#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
    float health;
    float speed;
    sf::Vector2f position;
    sf::Sprite enemySprite;
    // const sf::Texture& enemyTexture;

public:
    // constructors (initialization & cc)
    Enemy(float health_, float speed_, const sf::Vector2f& position_); // const sf::Texture& texture_);
    Enemy(const Enemy& other);

    // op=
    Enemy& operator=(const Enemy& other);

    // destructor
    ~Enemy();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);

    // methods
    // [[maybe_unused]] void drawEnemies(sf::RenderWindow& window) const;
};

#endif //ENEMY_H
