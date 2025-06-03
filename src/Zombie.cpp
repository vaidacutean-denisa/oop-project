#include "../headers/Zombie.h"

Zombie::Zombie(float health_, float enemySpeed_, const sf::Vector2f& enemyPosition, float attackCooldown_)
                : Enemy(health_, enemySpeed_, enemyPosition, attackCooldown_), zombieDamage(0) {
	distanceScalingFactor = 5.5f;
}

void Zombie::updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) {
    followPlayer(playerCenter, windowSize, playerSize);
}

float Zombie::getMinDistanceToPlayer(const sf::Vector2f &playerSize) {
	return (playerSize.x + getSize().x) / distanceScalingFactor;
}

// void Zombie::updateHitbox() {
//     sf::FloatRect bounds = getSprite().getGlobalBounds();
//
//     float offsetX = bounds.width * 0.2f;
//     float offsetY = bounds.height * 0.2f;
//
//     hitbox = sf::FloatRect(
//         bounds.left + offsetX,
//         bounds.top + offsetY,
//         bounds.width - (offsetX * 2),
//         bounds.height - (offsetY * 2)
//     );
// }


// void Zombie::adjustSpeed(float currentLevel)