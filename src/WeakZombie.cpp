#include "../headers/WeakZombie.h"

WeakZombie::WeakZombie(const sf::Texture& weakZombieTexture) : Zombie(100.f, 4.6f, {0.f, 0.f}, 1.5f)
{
	enemySprite.setTexture(weakZombieTexture);
    enemySprite.setScale(sf::Vector2f(1.7f, 1.7f));

	zombieDamage = 6.f;
	hitboxScalingFactor = 0.45f;
    // pentru debug
    // std::cout << "sprite size: " << getSprite().getGlobalBounds().width << "x" << getSprite().getGlobalBounds().height << std::endl;
}

WeakZombie::WeakZombie(const WeakZombie& other) : Zombie(other) {
	enemySprite.setTexture(*other.enemySprite.getTexture());
	enemySprite.setScale(other.enemySprite.getScale());
}


void WeakZombie::attackPlayer(Player& player) {
	if (enemySprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
		if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) {
			player.takeDamage(zombieDamage);
			attackClock.restart();
		}
}

void WeakZombie::drawImplementation(sf::RenderWindow &window) const {
	window.draw(enemySprite);
}
