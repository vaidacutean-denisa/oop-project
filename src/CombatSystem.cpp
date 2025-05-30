#include "../headers/CombatSystem.h"

std::vector<Bullet> CombatSystem::processBulletHits(const std::vector<Bullet>& bullets, const std::vector<std::unique_ptr<Enemy>>& enemies, float damage) {
    std::vector<Bullet> activeBullets;

    for (auto& bullet : bullets) {
        bool hitEnemy = false;

        for (const auto& enemy : enemies) {
            sf::FloatRect enemyBounds = enemy->getSprite().getGlobalBounds();

            const auto scalingFactor = 0.45f;

            float offsetX = enemyBounds.width * scalingFactor;
            float offsetY = enemyBounds.height * scalingFactor;

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

void CombatSystem::removeDeadEnemies(std::vector<std::unique_ptr<Enemy>>& enemies) {
    auto it = enemies.begin();
    while (it != enemies.end()) {
        if ((*it)->isDead())
            it = enemies.erase(it);
        else
            ++it;
    }
}

void CombatSystem::handleCombat(std::vector<Bullet>& bullets, std::vector<std::unique_ptr<Enemy>>& enemies, const Weapon& currentWeapon) {
    float damage = currentWeapon.getDamage();

    bullets = processBulletHits(bullets, enemies, damage);
    removeDeadEnemies(enemies);
}