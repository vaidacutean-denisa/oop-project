#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Ammunition.h"

class Weapon {
    std::string name;
    float damage;
    float reloadTime;               // concept doar teoretic so far
    float ammoCapacity;             // capacitatea incarcatorului
    float currentAmmo;              // cate gloante are pe incarcator
    Ammunition ammo;                // tipul de gloante folosite
    float bulletSpeed;

public:
    // constructors (initialization & cc)
    Weapon(std::string  name_, float dmg_, float rTime_, float capacity_, float currentAmmo_, Ammunition  ammo_);
    Weapon(const Weapon& other) = default;

    // destructor
    ~Weapon() = default;

    // op=
    Weapon& operator=(const Weapon& other);

    // methods
    [[maybe_unused]] void applyDamageBoost(float boostMultiplier);
    bool shoot();
    void reload();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);

    // getters & setters
    [[nodiscard]] float getDamage() const;
    [[nodiscard]] const std::string& getWeaponName() const;
    [[nodiscard]] float getBulletSpeed() const;
};

#endif //WEAPON_H
