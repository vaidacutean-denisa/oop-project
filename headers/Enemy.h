#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../headers/Player.h"

class Enemy {
protected:
    float health;
    float enemySpeed;
    sf::Vector2f enemyPosition;
    sf::Sprite enemySprite;

	sf::Clock attackClock;
	float attackCooldown;

	float scalingFactor;

	// methods
	virtual void drawImplementation(sf::RenderWindow& window) const = 0;

    // getters & setters
    const sf::Vector2f& getPosition() const;
    void setTexture(const sf::Texture &texture);

public:
    // constructors (initialization & cc)
	Enemy() : health(100), enemySpeed(1.f), enemyPosition(0.f,0.f), attackCooldown(0.f), scalingFactor(1.f) {}
    Enemy(float health_, float enemySpeed_, const sf::Vector2f& enemyPosition_, float attackCooldown_);
    Enemy(const Enemy& other);

    // op=
    Enemy& operator=(const Enemy& other);

    // destructor
    virtual ~Enemy();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);

    // methods
    void drawEnemies(sf::RenderWindow& window) const;
    // sf::Sprite& scaleEnemies();

    virtual void followPlayer(const sf::Vector2f& playerPosition, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize);
	virtual float getMinDistanceToPlayer(const sf::Vector2f& playerSize) = 0;

	virtual void updateEnemies(const sf::Vector2f& playerPosition, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) = 0;
    virtual void attackPlayer(Player& player) = 0;

    bool checkCollision(const Enemy& other) const;
    void resolveCollision(const std::vector<std::unique_ptr<Enemy>>& enemies);

    void takeDamage(float amount);
    bool isDead() const;

    // getters & setters
    virtual float getSpeed() const;
    const sf::Sprite& getSprite() const;
	virtual sf::Vector2f getSize() const = 0;
	void setPosition(const sf::Vector2f& enemyPosition_);
};

#endif //ENEMY_H
