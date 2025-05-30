#include "Skeleton.h"
#include <cmath>

Skeleton::Skeleton(const sf::Texture& skeletonTexture, const sf::Texture& projectileTexture_)
	: Enemy(140.f, 3.5f, {0, 0}, 3.5f),
	   projectileTexture(projectileTexture_), shootingCooldown(2.f), shootTimer(0.f), projectileSpeed(600.f)
{
	enemySprite.setTexture(skeletonTexture);

	collisionDamage = 4.f;
	enemySprite.setPosition(enemyPosition);
	scalingFactor = 1.5f;
	projectileDamage = 7.f;

	enemySprite.setScale(0.45f, 0.45f);
}

sf::Vector2f Skeleton::getSize() const {
	return enemySprite.getGlobalBounds().getSize();
}

float Skeleton::getMinDistanceToPlayer(const sf::Vector2f &playerSize) {
	return (playerSize.x + getSize().x) * scalingFactor;
}

void Skeleton::updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) {
	followPlayer(playerCenter, windowSize, playerSize);
}

void Skeleton::attackPlayer(Player &player) {
	if (enemySprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
		if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) {
			player.takeDamage(collisionDamage);
			attackClock.restart();
		}

	if (shootTimer >= shootingCooldown) {
		sf::Vector2f skeletonCenter = enemySprite.getPosition() + getSize() / 2.f;
		sf::Vector2f playerCenter = player.getCenterPosition();

		sf::Vector2f direction = playerCenter - skeletonCenter;
		const float dx = direction.x;
		const float dy = direction.y;

		float length = std::sqrt(dx * dx + dy * dy);

		if (length != 0)
			direction /= length;

		projectiles.emplace_back(projectileTexture, projectileSpeed, direction, skeletonCenter);
		shootTimer = 0.f;
	}
}

void Skeleton::processProjectiles(float deltaTime, const sf::RenderWindow &window, Player& player) {
	for (Bullet& projectile : projectiles)
		projectile.updateBullet(deltaTime);

	std::vector<Bullet> activeProjectiles;
	for (const Bullet& projectile : projectiles) {
		if (projectile.getBounds().intersects(player.getSprite().getGlobalBounds())) {
			player.takeDamage(projectileDamage);
			continue;
	}

		if (!projectile.isOutOfBounds(window))
			activeProjectiles.push_back(projectile);
	}

	projectiles = std::move(activeProjectiles);
	shootTimer += deltaTime;
}

void Skeleton::drawProjectiles(sf::RenderWindow &window) const {
	for (const Bullet& projectile : projectiles)
		projectile.drawBullet(window);
}

void Skeleton::drawImplementation(sf::RenderWindow &window) const {
	window.draw(enemySprite);
}