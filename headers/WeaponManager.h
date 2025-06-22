#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <memory>
#include <vector>

#include "../headers/Ammunition.h"
#include "../headers/Weapon.h"

class WeaponManager {
	std::vector<std::unique_ptr<Weapon>> weapons;

	// methods
	void initializeWeapons();

public:
	// constructor
	WeaponManager();

	// methods
	std::vector<Weapon> createPlayerWeapons() const;
};

#endif //WEAPONMANAGER_H
