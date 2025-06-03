#ifndef DEATH_H
#define DEATH_H

#include "../headers/Enemy.h"

class Death : public Enemy {
	float healAmount;
	float collisionDamage;
	float maxHealth;

public:
	// constructor
	explicit Death(const sf::Texture& deathTexture);
	Death(const Death &other);

	Enemy* clone() const override {
		return new Death(*this);
	}

	// methods
	void updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u &windowSize, const sf::Vector2f &playerSize) override;
	void attackPlayer(Player &player) override;
	void regenerateHealth(float amount);

	float getMinDistanceToPlayer(const sf::Vector2f &playerSize) override;
	void drawImplementation(sf::RenderWindow &window) const override;
};

#endif //DEATH_H
