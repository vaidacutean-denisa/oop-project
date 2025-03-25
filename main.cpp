#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

class Ammunition {
    std::string type;           // tipul munitiei
    int quantity;               // ar trebui sa fie cantitatea pe care o are player-ul in inventar (inexistent din pacate)

public:
    // constructors
    explicit Ammunition(std::string  type_, int quantity_);

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Ammunition& ammo) {
        os << "Ammo type = " << ammo.type << '\n'
           << "Quantity = " << ammo.quantity << "\n";
        return os;
    }
};

Ammunition::Ammunition(std::string  type_, int quantity_)
    : type(std::move(type_)), quantity(quantity_) { }

class Weapon {
    std::string name;
    float damage;
    float reloadTime;               // concept doar teoretic so far
    float ammoCapacity;             // capacitatea incarcatorului
    float currentAmmo;              // cate gloante are pe incarcator
    Ammunition ammo;                // tipul de gloante folosite

public:
    // constructors (initialization & cc)
    explicit Weapon(std::string  name_, float dmg_, float rTime_, float capacity_, float currentAmmo_, Ammunition  ammo_);
    Weapon(const Weapon& other);

    // destructor
    ~Weapon() = default;

    // op=
    Weapon& operator=(const Weapon& other);

    // methods
    void applyDamageBoost(float boostMultiplier);

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Weapon: " << weapon.name <<'\n'
           << "Damage = " << weapon.damage << '\n'
           << "Reload time = " << weapon.reloadTime << '\n'
           << "Ammo capacity = " << weapon.ammoCapacity << '\n'
           << "Current ammo = " << weapon.currentAmmo << '\n'
           << weapon.ammo << '\n';
        return os;
    }

    // getters & setters
    [[nodiscard]] float getDamage() const { return damage; }
    [[nodiscard]] std::string getWeaponName() const { return name; }
};

Weapon::Weapon(std::string  name_, float dmg_, float rTime_, float capacity_, float currentAmmo_, Ammunition  ammo_)
    : name(std::move(name_)), damage(dmg_), reloadTime(rTime_), ammoCapacity(capacity_), currentAmmo(currentAmmo_), ammo(std::move(ammo_)) {}

Weapon::Weapon(const Weapon& other) : name(other.name), damage(other.damage), reloadTime(other.reloadTime),
                                        ammoCapacity(other.ammoCapacity), currentAmmo(other.currentAmmo), ammo(other.ammo)
{
    // std::cout << "constructor de copiere apelat (weapon)\n";
}

Weapon& Weapon::operator=(const Weapon& other) {
    name = other.name;
    damage = other.damage;
    reloadTime = other.reloadTime;
    ammoCapacity = other.ammoCapacity;
    currentAmmo = other.currentAmmo;
    ammo = other.ammo;
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

class Player {
    int health;
    float speed;
    float x, y;                                 // eventualele coordonate pe harta
    std::vector<Weapon> weapons;
    int currentWeaponIndex;

public:
    // constructors
    explicit Player(int health_, float speed_, float x_, float y_, const std::vector<Weapon>& weapons_);

    // methods
    void selectWeapon(int index);

    void applyDamageBoost(float boostMultiplier);
    void applyHealthBoost(int boostAmount);
    void applySpeedBoost(float boostAmount);

    [[nodiscard]] int getHealth() const { return health; }
    [[nodiscard]] float getSpeed() const { return speed; }

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player - Health = " << player.health << '\n'
           << "Speed = " << player.speed << '\n'
           << player.weapons[player.currentWeaponIndex] << '\n';
        return os;
    }
};

Player::Player(int health_, float speed_, float x_, float y_, const std::vector<Weapon>& weapons_)
    : health(health_), speed(speed_), x(x_), y(y_), weapons(weapons_), currentWeaponIndex(0) {}

void Player::selectWeapon(int index) {
    if (!weapons.empty() && index >= 0 && index < static_cast<int>(weapons.size())) {
        currentWeaponIndex = index;
        std::cout << "Selected weapon: " << weapons[currentWeaponIndex].getWeaponName() << '\n';
        std::cout << "Your weapon has a damage of: " << weapons[currentWeaponIndex].getDamage() <<". Great choice!\n";
    }
    else {
        std::cout << "Invalid weapon index!\n";
    }
}

void Player::applyDamageBoost(const float boostMultiplier) {
    if (!weapons.empty()) {
        weapons[currentWeaponIndex].applyDamageBoost(boostMultiplier);
    }
}

void Player::applyHealthBoost(int boostAmount) {
    const int maxHealth = 150;
    if (health < maxHealth)                                                     // suppose maxhealth = 150 (to be reviewed)
        health += boostAmount;
}

void Player::applySpeedBoost(float boostAmount) {
    speed += boostAmount;
}

class Enemy {
    int health;
    float speed;
    float x, y;

public:
    // constructors (initialization & cc)
    explicit Enemy(int health_, float speed_, float x_, float y_);
    Enemy(const Enemy& other);

    // op=
    Enemy& operator=(const Enemy& other);

    // destructor
    ~Enemy();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
        os << "Enemy - health = " << enemy.health << '\n'
           << "Speed = " << enemy.speed << '\n'
           << "Position: (" << enemy.x << ", " << enemy.y << ")\n";
        return os;
    }
};

Enemy::Enemy(const Enemy& other) : health(other.health), speed(other.speed), x(other.x), y(other.y) {
    std::cout << "cc Enemy\n";
}

Enemy& Enemy::operator=(const Enemy& other) {
    std::cout << "replicating enemies.. a true test of my patience (op=)\n";
    health = other.health;
    speed = other.speed;
    x = other.x;
    y = other.y;
    return *this;
}

Enemy::~Enemy() {
    std::cout << "One step closer to survival.. (destructor enemy)\n";
}

Enemy::Enemy(int health_, float speed_, float x_, float y_)
    : health(health_), speed(speed_), x(x_), y(y_) {}

class Perks {
    float x, y;
    float duration;                 // concept doar teoretic so far
    std::string  type;

public:
    // constructors
    explicit Perks(float x_, float y_, float duration_, std::string  type_) : x(x_), y(y_), duration(duration_), type(std::move(type_)) {}

    // methods
    void applyPerk(Player& player) const;

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Perks& perk) {
        os << "Perks - Type: " << perk.type << '\n'
           << "Position: (" << perk.x << ", " << perk.y << ")" << '\n'
           << "Duration: " << perk.duration << " seconds";
        return os;
    }

};

void Perks::applyPerk(Player& player) const {
    if (type == "health") {
        player.applyHealthBoost(20);
        // std::cout << "Health boost applied.\n";
        if (player.getHealth() > 75)
            std::cout << "You're at " << player.getHealth() << " health. You're in good shape!\n";
        else if (player.getHealth() > 35)
            std::cout << "You've got " << player.getHealth() << " health. Keep pushing!\n";
        else
            std::cout << player.getHealth() << " health left. You're hanging by a thread, but hey, it's a strong thread! Maybe avoid the next hit?\n";
    }
    else if (type == "speed") {
        player.applySpeedBoost(4.5f);
        std::cout << "Speed boost activated. Time to leave everyone in the dust.\n";
    }
    else {
        player.applyDamageBoost(1.5f);
        std::cout << "Your hits just got a bit more.. convincing.\n";
    }
}

int main() {
    Ammunition ak_Ammo = Ammunition("7.62mm", 60);
    Ammunition pistol_Ammo = Ammunition("5.56mm", 30);
    Ammunition m4_Ammo = Ammunition("9mm", 60);
    Ammunition shotgun_Ammo = Ammunition("12 Gauge", 20);

    Weapon ak("AK-47", 17, 2.5f, 30, 30, ak_Ammo);
    Weapon pistol("Pistol", 7.0f, 1.3f, 15, 15, pistol_Ammo);
    Weapon m4("M416", 14.5f, 1.8f, 30, 30, m4_Ammo);
    Weapon shotgun("Shotgun", 40, 5.5f, 5, 5, shotgun_Ammo);

    Player denisa(100, 15.5f, 6, 7, {ak, pistol, m4, shotgun});

    // pentru a verifica op=, cc
    Enemy antonia(100, 17.5f, -2, -6);
    Enemy zombie1 = Enemy(100, 17.5f, 8, 10);
    const Enemy& zombie2 = antonia;                  // cc   (creeaza un nou obiect (zombie1) facand o copie a unui obiect deja existent (antonia))
    zombie1 = zombie2;                               // op=  (atribuie valoarea unui obiect (zombie2) altui obiect deja existent (zombie1))

    std::cout << zombie1 << " " << antonia << " " << zombie2 << '\n';
    std::vector<Perks> listOfPerks = {                                          // ar putea fi clase derivate? (de revazut) + bonus de ammo crate (idee)
        Perks(6, 14, 0, "health"),
        Perks(4, 3, 10,"speed"),
        Perks(-5, 9, 10, "damage"),                        // de rezolvat cu durata bonusurilor; cel de health nu va avea durata
    };

    int weaponIndex = 0;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Decide your fate - select a weapon by picking a number from 1 to 4: \n";
        std::cin >> weaponIndex;

        if (weaponIndex >= 1 && weaponIndex <= 4)
            validInput = true;
        else
            std::cout << "Invalid selection. Please choose a number between 1 and 4.\n";
    }

    weaponIndex--;
    denisa.selectWeapon(weaponIndex);

    // testarea functionalitatii de aplicare a bonusurilor
    std::cout << "The groundwork is laid. Time to start building something legendary.\n";
    std::cout << "Player stats before applying perks: \n" << denisa;

    std::cout << "Applying perks..\n";
    for (const Perks& type : listOfPerks) {                                           // parcurge lista de perks si le aplica asupra player-ului
        std::cout << type << '\n';          // pentru op<<
        type.applyPerk(denisa);
    }

    std::cout << "Fully upgraded. Time to paint the town red.\n";
    std::cout << "Player stats after applying perks: \n" << denisa;

    // in lucru...
    // sf::RenderWindow window(sf::VideoMode({800, 600}), "My window", sf::Style::Default);
    // window.setVerticalSyncEnabled(true);
    //
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //
    //     sf::Color customColor(13, 6, 60);
    //     window.clear(customColor);
    //
    //     window.display();
    // }

}