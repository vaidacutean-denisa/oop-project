#ifndef WEAKZOMBIE_H
#define WEAKZOMBIE_H

#include "../headers/Zombie.h"

class WeakZombie : public Zombie {

public:
    // constructor
    explicit WeakZombie(const sf::Texture &weakZombieTexture);
	WeakZombie(const WeakZombie &other);

	Enemy * clone() const override {
		return new WeakZombie(*this);
	}

    // methods
    void attackPlayer(Player& player) override;
	void drawImplementation(sf::RenderWindow &window) const override;

    // getters & setters
};

#endif //WEAKZOMBIE_H
