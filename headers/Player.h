#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Bullet.h"
#include <memory>

class Player {
    int health;
    float speed;
    float normalSpeed;                                                          // pentru a reveni la viteza normala dupa ce trage
    sf::Vector2f position;

    int currentWeaponIndex;
    std::vector<Weapon> weapons;
    std::vector<Bullet> bullets;
    sf::Texture bulletTexture;

    sf::Sprite playerSprite;

    sf::Clock shootingClock;
    float shootCooldown;
    sf::Clock slowTimer;                                                        // viteza jucatorului scade atunci cand trage cu arma
    float slowFactor;

public:
    // constructors
    Player(int health_, float speed_, sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_);

    // methods
    void selectWeapon(int index);

    void applyDamageBoost(float boostMultiplier);
    void applyHealthBoost(int boostAmount);
    void applySpeedBoost(float boostAmount);

    void drawPlayer(sf::RenderWindow& window) const;
    void updateSpritePosition();
    void movePlayer(float dx, float dy, const sf::RenderWindow& window);
    void rotatePlayer(float angle);

    void shoot();
    void drawShooting(sf::RenderWindow& window) const;
    void processBullets(float deltaTime, const sf::RenderWindow& window);

    // getters & setters
    [[nodiscard]] int getHealth() const;

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif //PLAYER_H
