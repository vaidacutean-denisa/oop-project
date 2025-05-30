#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "../headers/Bullet.h"
#include "../headers/Enemy.h"
#include "../headers/Weapon.h"

#include <vector>
#include <memory>

class CombatSystem {
public:
    static std::vector<Bullet> processBulletHits(const std::vector<Bullet>& bullets, const std::vector<std::unique_ptr<Enemy>>& enemies, float damage);
    static void removeDeadEnemies(std::vector<std::unique_ptr<Enemy>>& enemies);
    static void handleCombat(std::vector<Bullet>& bullets, std::vector<std::unique_ptr<Enemy>>& enemies, const Weapon& currentWeapon);
};

#endif //COMBATSYSTEM_H


