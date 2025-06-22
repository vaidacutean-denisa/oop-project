#include "../headers/CombatSystem.h"

std::vector<Bullet> CombatSystem::processBulletHits(const std::vector<Bullet>& bullets, const std::vector<std::unique_ptr<Enemy>>& enemies, float damage) {
    std::vector<Bullet> activeBullets;

    for (auto& bullet : bullets) {
        bool hitEnemy = false;

        for (const auto& enemy : enemies) {
            sf::FloatRect enemyBounds = enemy->getSprite().getGlobalBounds();

            const auto scalingFactor = enemy->getHitboxFactor();

            const float offsetX = enemyBounds.width * scalingFactor;
            const float offsetY = enemyBounds.height * scalingFactor;

            sf::FloatRect hitbox(
                enemyBounds.left + offsetX,
                enemyBounds.top + offsetY,
                enemyBounds.width - (offsetX * 2),
                enemyBounds.height - (offsetY * 2)
            );

            if (bullet.getBounds().intersects(hitbox)) {
                enemy->takeDamage(damage);
                hitEnemy = true;
                break;
            }
        }
        if (!hitEnemy)
            activeBullets.push_back(bullet);
    }
    return activeBullets;
}

int CombatSystem::removeDeadEnemies(std::vector<std::unique_ptr<Enemy> > &enemies) {
	int enemiesKilled = 0;

	auto it = enemies.begin();
    while (it != enemies.end()) {
        if ((*it)->isDead()) {
	        it = enemies.erase(it);
			enemiesKilled++;
        }
        else
            ++it;
    }

	return enemiesKilled;
}

void CombatSystem::handleCombat(std::vector<Bullet>& bullets, std::vector<std::unique_ptr<Enemy>>& enemies, const Weapon& currentWeapon, PerkManager& perkManager, const sf::Vector2u& windowSize) {
	float damage = currentWeapon.getDamage();

    bullets = processBulletHits(bullets, enemies, damage);
    int enemiesKilled = removeDeadEnemies(enemies);

	for (int i = 0; i < enemiesKilled; i++) {
		perkManager.onEnemyKilled(windowSize);
	}
}
