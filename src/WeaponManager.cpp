#include "../headers/WeaponManager.h"

WeaponManager::WeaponManager() {
	initializeWeapons();
}

void WeaponManager::initializeWeapons() {
	auto ak_Ammo = std::make_unique<Ammunition>("7.62mm", 60);
	auto pistol_Ammo = std::make_unique<Ammunition>("5.56mm", 30);
	auto m4_Ammo = std::make_unique<Ammunition>("9mm", 60);
	auto shotgun_Ammo = std::make_unique<Ammunition>("12 Gauge", 20);

	weapons.push_back(std::make_unique<Weapon>("AK-47", 22.f, 2.5f, 30, 30, std::move(*ak_Ammo)));
	weapons.push_back(std::make_unique<Weapon>("Pistol", 14.f, 1.3f, 15, 15, std::move(*pistol_Ammo)));
	weapons.push_back(std::make_unique<Weapon>("M416", 20.5f, 1.8f, 30, 30, std::move(*m4_Ammo)));
	weapons.push_back(std::make_unique<Weapon>("Shotgun", 40, 5.5f, 5, 5, std::move(*shotgun_Ammo)));
}

std::vector<Weapon> WeaponManager::createPlayerWeapons() const {
	std::vector<Weapon> playerWeapons;
	for (const auto& weapon : weapons)
		playerWeapons.push_back(*weapon);

	return playerWeapons;
}
