#include "Player.h"
#include <cmath>
#include <memory>

constexpr float pi = 3.1415f;

int Player::getHealth() const { return health; }

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player - Health = " << player.health << '\n'
       << "Speed = " << player.speed << '\n'
       << player.weapons[player.currentWeaponIndex] << '\n';
    return os;
}

Player::Player(int health_, float speed_, sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_)
    : health(health_), speed(speed_), normalSpeed(speed_), position(position_), currentWeaponIndex(0), weapons(weapons_), shootCooldown(0.3f), slowFactor(0.5f) {

    playerSprite.setTexture(playerTexture_);
    playerSprite.setScale(0.6f, 0.6f);

    sf::FloatRect bounds = playerSprite.getLocalBounds();                                   // (floatRect -> abstractizarea unui dreptunghi; sf::RectangleShape este un obiect desenabil)
    playerSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);                    // calculeaza originea sprite-ului astfel incat punctul de referinta al acestuia sa fie in centru
                                                                                            // punctul de referinta este implicit in coltul stanga sus -> comportament neasteptat la rotire
    updateSpritePosition();

    if (!bulletTexture.loadFromFile("assets/images/bullet.png")) {
        std::cerr << "Failed to load bullet texture!" << std::endl;
    }
}

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
    constexpr int maxHealth = 150;
    if (health < maxHealth)                                                     // suppose maxhealth = 150 (to be reviewed)
        health += boostAmount;
}

void Player::applySpeedBoost(float boostAmount) {
    speed += boostAmount;
}

void Player::drawPlayer(sf::RenderWindow& window) const {
    window.draw(playerSprite);
}

void Player::updateSpritePosition() {
    playerSprite.setPosition(position.x, position.y);
}

void Player::movePlayer(float dx, float dy, const sf::RenderWindow& window) {
    if (slowTimer.getElapsedTime().asSeconds() > shootCooldown) {
        speed = normalSpeed;
    }
    float length = std::sqrt(dx * dx + dy * dy);                              // |v| = sqrt(dx^2 + dy^2), lungimea unui vector
    if (length != 0) {
        dx /= length;                                                           // normalizare; impart coordonatele vectorului la lungimea lui astfel incat |v_normalizat| = 1
        dy /= length;                                                           // fara normalizare, s-ar fi deplasat mai repede pe diagonala decat in alte directii
    }

    float tempX = position.x + dx * speed;
    float tempY = position.y + dy * speed;

    const sf::Vector2u windowSize = window.getSize();
    const auto windowWidth = static_cast<float>(windowSize.x);
    const auto windowHeight = static_cast<float>(windowSize.y);

    tempX = std::clamp(tempX, 0.f, windowWidth);                       // verifica si previne iesirea caracterului din limitele ferestrei
    tempY = std::clamp(tempY, 0.f, windowHeight);                      // de ex. daca pozitia player-ului depaseste windowHeight, tempY va lua valoarea lui windowHeight
                                                                                // analog pentru cazul in care pozitia scade sub 0 (marginea stanga / sus)
    position.x = tempX;
    position.y = tempY;

    playerSprite.setPosition(position.x, position.y);
}

void Player::rotatePlayer(float angle) {
    playerSprite.setRotation(angle);
}

void Player::shoot() {
    if (shootingClock.getElapsedTime().asSeconds() >= shootCooldown) {                      // jucatorul are un shooting cooldown pentru a preveni spam-ul
        if (!weapons.empty()) {
            Weapon& currentWeapon = weapons[currentWeaponIndex];

            if (!currentWeapon.shoot()) {
                currentWeapon.reload();
                std::cout << "Reloading..\n";
            }

            float angle = playerSprite.getRotation();                                       // calculeaza directia glontului in functie de directia in care se uita jucatorul
            float radians = angle * (pi / 180.f);
            sf::Vector2f direction(std::cos(radians), std::sin(radians));               // transforma unghiul de rotatie al jucatorului intr-un vector de directie pentru glont (vector unitate)

            float bulletSpeed = currentWeapon.getBulletSpeed();

            sf::Vector2f visualOffset(50.f, 21.f);                                                                   // un offset vizual ca sa para ca glontul iese din arma
            sf::Vector2f rotatedOffset;                                                                                  // ! de revizuit totusi pentru ca implementarea nu ar trebui sa depinda de valori fixe
            rotatedOffset.x = visualOffset.x * std::cos(radians) - visualOffset.y * std::sin(radians);
            rotatedOffset.y = visualOffset.x * std::sin(radians) + visualOffset.y * std::cos(radians);

            sf::Vector2f bulletPosition = position + rotatedOffset;
            bullets.emplace_back(bulletTexture, bulletSpeed, direction, bulletPosition);

            speed = normalSpeed * slowFactor;
            slowTimer.restart();
        }
        shootingClock.restart();
    }
}

void Player::drawShooting(sf::RenderWindow &window) const {
    for (const Bullet& bullet : bullets) {
        bullet.drawBullet(window);
    }
}

void Player::processBullets(float deltaTime, const sf::RenderWindow& window) {
    for (Bullet& bullet : bullets)
        bullet.updateBullet(deltaTime);

    std::vector<Bullet> activeBullets;                                          // vector care contine doar gloantele vizibile pe ecran

    for (const Bullet& bullet : bullets) {
        if (!bullet.isOutOfBounds(window))
            activeBullets.push_back(bullet);
    }
    bullets = std::move(activeBullets);
}
