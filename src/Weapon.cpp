#include "Weapon.h"

std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
    os << "Weapon: " << weapon.name <<'\n'
       << "Damage = " << weapon.damage << '\n'
       << "Reload time = " << weapon.reloadTime << '\n'
       << "Ammo capacity = " << weapon.ammoCapacity << '\n'
       << "Current ammo = " << weapon.currentAmmo << '\n'
       << weapon.ammo << '\n';
    return os;
}

Weapon::Weapon(std::string  name_, float dmg_, float rTime_, float capacity_, float currentAmmo_, Ammunition  ammo_)
    : name(std::move(name_)), damage(dmg_), reloadTime(rTime_), ammoCapacity(capacity_),
      currentAmmo(currentAmmo_), ammo(std::move(ammo_)), bulletSpeed(1450) { }

// Weapon::Weapon(const Weapon& other) : name(other.name), damage(other.damage), reloadTime(other.reloadTime),
//                                         ammoCapacity(other.ammoCapacity), currentAmmo(other.currentAmmo), ammo(other.ammo)
// {
//     // std::cout << "constructor de copiere apelat (weapon)\n";
// }

Weapon& Weapon::operator=(const Weapon& other) {
    if (this != &other) {
        name = other.name;
        damage = other.damage;
        reloadTime = other.reloadTime;
        ammoCapacity = other.ammoCapacity;
        currentAmmo = other.currentAmmo;
        ammo = other.ammo;
        bulletSpeed = other.bulletSpeed;
    }
    return *this;
}

// Weapon::~Weapon() {
//     std::cout << name << " shattered into a thousand pieces, its purpose fulfilled. (destructor weapon)\n";
// }

void Weapon::applyDamageBoost(float boostMultiplier) {
    damage = damage * boostMultiplier;
    std::cout << "Weapon damage boosted by x" << boostMultiplier <<" - time to show your enemies who's in charge.\n";
    std::cout << "The updated damage is: " << damage << '\n';
}

bool Weapon::shoot() {
    if (currentAmmo > 0) {
        currentAmmo--;
        return true;
    }

    std::cout << "Empty magazine. You're on your own now.";
    return false;
}

void Weapon::reload() {                                                                 // trebuie modificat (e incomplet)
    currentAmmo += ammoCapacity - currentAmmo;
    std::cout << "Weapon reloaded. Full magazine: " << ammoCapacity << '\n';
}
float Weapon::getDamage() const { return damage; }
const std::string& Weapon::getWeaponName() const { return name; }
float Weapon::getBulletSpeed() const { return bulletSpeed; }
