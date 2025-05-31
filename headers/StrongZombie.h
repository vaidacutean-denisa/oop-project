#ifndef STRONGZOMBIE_H
#define STRONGZOMBIE_H

#include "../headers/Zombie.h"

class StrongZombie : public Zombie {
	float slowMultiplier;
	float slowDuration;

	bool isEnraged;

	// methods
	void enterEnragedState();

public:
	// constructor
	explicit StrongZombie(const sf::Texture &strongZombieTexture);
	StrongZombie(const StrongZombie &other);

	Enemy * clone() const override {
		return new StrongZombie(*this);
	}

	// methods
    void attackPlayer(Player& player) override;
	void updateEnemies(const sf::Vector2f &playerPosition, const sf::Vector2u &windowSize, const sf::Vector2f &playerSize) override;
	void drawImplementation(sf::RenderWindow& window) const override;
};

#endif //STRONGZOMBIE_H
