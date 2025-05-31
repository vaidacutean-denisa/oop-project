#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "../headers/Enemy.h"

class Zombie : public Enemy {

    // getters & setters
    sf::Vector2f getSize() const override;
    float getSpeed() const override;

protected:
	float zombieDamage;

public:
	// constructor
	Zombie(float health_, float enemySpeed_, const sf::Vector2f &enemyPosition, float attackCooldown_);
	Zombie(const Zombie& other) : Enemy(other), zombieDamage(other.zombieDamage) {}

	// methods
	void updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) override;
    // void updateHitbox();

	// getters & setters
	float getMinDistanceToPlayer(const sf::Vector2f &playerSize) override;

    // void attackPlayer(float &playerHealth) override;
};

#endif //ZOMBIE_H
