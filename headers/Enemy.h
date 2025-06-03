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

	float distanceScalingFactor;
	float hitboxScalingFactor;

	// methods
	virtual void drawImplementation(sf::RenderWindow& window) const = 0;
	void followPlayer(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize);

    // getters & setters
    const sf::Vector2f& getPosition() const;
    void setTexture(const sf::Texture &texture);

public:
    // constructors (initialization & cc)
    Enemy(float health_, float enemySpeed_, const sf::Vector2f& enemyPosition_, float attackCooldown_);
    Enemy(const Enemy& other);

	virtual Enemy* clone() const = 0;

    // op=
    Enemy& operator=(const Enemy& other);

    // destructor
    virtual ~Enemy();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);

    // methods
    void drawEnemies(sf::RenderWindow& window) const;
    // sf::Sprite& scaleEnemies();

	virtual float getMinDistanceToPlayer(const sf::Vector2f& playerSize) = 0;

	virtual void updateEnemies(const sf::Vector2f& playerPosition, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) = 0;
    virtual void attackPlayer(Player& player) = 0;

    bool checkCollision(const Enemy& other) const;
    void resolveCollision(const std::vector<std::unique_ptr<Enemy>>& enemies);

    void takeDamage(float amount);
    bool isDead() const;

    // getters & setters
    const sf::Sprite& getSprite() const;
	void setPosition(const sf::Vector2f& enemyPosition_);
	float getSpeed() const;
	sf::Vector2f getSize() const;
	float getHitboxFactor() const;
};

#endif //ENEMY_H
