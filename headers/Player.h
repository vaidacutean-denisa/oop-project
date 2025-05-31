#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Bullet.h"
#include <memory>

class Player {
    float health;
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
	bool slowedByShooting;

	float slowTimeLeft = 0.f;

public:
    // constructors
    Player(float health_, float speed_, sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_);

    // methods
    void selectWeapon(int index);

    void applyDamageBoost(float boostMultiplier);
    void applyHealthBoost(float boostAmount);
    void applySpeedBoost(float boostAmount);

    void drawPlayer(sf::RenderWindow& window) const;
    void updateSpritePosition();

    void movePlayer(float dx, float dy, const sf::RenderWindow& window);
    void rotatePlayer(float angle);

    void shoot();
    void drawShooting(sf::RenderWindow& window) const;
    void processBullets(float deltaTime, const sf::RenderWindow &window);
	sf::Vector2f getCenterPosition() const;

	void takeDamage(float amount);
	void applySlowness(const float slowMultiplier, const float slowDuration);
	void updateEffectStatus(float deltaTime);

	bool isDead() const;

	void clearBullets();
	void resetPlayerValues();

	// getters & setters
    // float getHealth() const; momentan nu e folosita
    sf::Vector2f getPosition() const;
    std::vector<Bullet>& getBullets();
    const Weapon& getCurrentWeapon() const;
	sf::Vector2f getPlayerSize() const;
	sf::Sprite getSprite() const;
	std::vector<Weapon *> getWeapons();

	// op <<
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif //PLAYER_H
