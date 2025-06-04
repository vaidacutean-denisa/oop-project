#include "../headers/StrongZombie.h"

StrongZombie::StrongZombie(const sf::Texture& strongZombieTexture) : Zombie(180.f, 5.f, {0.f, 0.f}, 2.3f),
			slowMultiplier(0.15f), slowDuration(1.3f), isEnraged(false)
{
	enemySprite.setTexture(strongZombieTexture);
	enemySprite.setScale(0.7f, 0.7f);
	zombieDamage = 10.f;
	hitboxScalingFactor = 0.85f;
}

StrongZombie::StrongZombie(const StrongZombie& other)
	 : Zombie(other) , slowMultiplier(other.slowMultiplier) , slowDuration(other.slowDuration), isEnraged(other.isEnraged) {
	enemySprite.setTexture(*other.enemySprite.getTexture());
	enemySprite.setScale(other.enemySprite.getScale());
}


void StrongZombie::enterEnragedState() {
	isEnraged = true;
	enemySprite.setScale(1.f, 1.f);

	float speedMultiplier = 1.3f;
	enemySpeed *= speedMultiplier;

	float damageMultiplier = 5.f;
	zombieDamage += damageMultiplier;
}

void StrongZombie::attackPlayer(Player& player) {
	if (enemySprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
		if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) {
			player.takeDamage(zombieDamage);
			player.applySlowness(slowMultiplier, slowDuration);				// de tinut cont ca zombie-ul are attack cooldown
			attackClock.restart();
		}
}

void StrongZombie::updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) {
	if (!isEnraged && health < 45.f)
		enterEnragedState();

	Zombie::updateEnemies(playerCenter, windowSize, playerSize);
}

void StrongZombie::drawImplementation(sf::RenderWindow &window) const {
	window.draw(enemySprite);
}