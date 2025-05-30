#include "../headers/WeakZombie.h"

WeakZombie::WeakZombie(const sf::Texture& weakZombieTexture) : Zombie(100.f, 4.f, {0.f, 0.f}, 1.5f)
{
	enemySprite.setTexture(weakZombieTexture);
    enemySprite.setScale(sf::Vector2f(1.7f, 1.7f));

	zombieDamage = 6.f;
    // pentru debug
    // std::cout << "sprite size: " << getSprite().getGlobalBounds().width << "x" << getSprite().getGlobalBounds().height << std::endl;
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
