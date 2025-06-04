#include "../headers/Death.h"

Death::Death(const sf::Texture& deathTexture) : Enemy(350.f, 6.f, {0, 0}, 2.f),
			healAmount(5.f), collisionDamage(12.f), maxHealth(health) {
	enemySprite.setTexture(deathTexture);
	enemySprite.setPosition(enemyPosition);

	enemySprite.setScale(0.9f, 0.9f);
	hitboxScalingFactor = 0.8f;
	distanceScalingFactor = 0.2f;
}

Death::Death(const Death& other) : Enemy(other), healAmount(other.healAmount), collisionDamage(other.collisionDamage), maxHealth(other.health) {
	enemySprite.setTexture(*other.enemySprite.getTexture());
	enemySprite.setScale(other.enemySprite.getScale());
}


void Death::updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u &windowSize, const sf::Vector2f &playerSize) {
	followPlayer(playerCenter, windowSize, playerSize);
}

void Death::attackPlayer(Player &player) {
	if (enemySprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
		if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) {
			player.takeDamage(collisionDamage);
			regenerateHealth(healAmount);
			attackClock.restart();
		}
}

void Death::regenerateHealth(float amount) {
	health += amount;
	if (health > maxHealth)
		health = maxHealth;
}

float Death::getMinDistanceToPlayer(const sf::Vector2f &playerSize) {
	return (playerSize.x + getSize().x) * distanceScalingFactor;
}

void Death::drawImplementation(sf::RenderWindow &window) const {
	window.draw(enemySprite);
}