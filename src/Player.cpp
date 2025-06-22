#include "../headers/Player.h"
#include <cmath>
#include <memory>
#include "../headers/GameExceptions.h"

constexpr float pi = 3.1415f;

Player::Player(float health_, float speed_, const sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_)
    : health(health_), maxHealthVisual(health_), maxHealth(150.f), speed(speed_), normalSpeed(speed_), baseSpeed(normalSpeed),  position(position_),
	  currentWeaponIndex(0), weapons(weapons_), shootCooldown(0.3f), slowFactor(0.5f), slowedByShooting(false), shieldDuration(10.f) {

    playerSprite.setTexture(playerTexture_);
    playerSprite.setScale(0.6f, 0.6f);

    const sf::FloatRect bounds = playerSprite.getLocalBounds();                             // (floatRect -> abstractizarea unui dreptunghi; sf::RectangleShape este un obiect desenabil)
    playerSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);                    // calculeaza originea sprite-ului astfel incat punctul de referinta al acestuia sa fie in centru
                                                                                            // punctul de referinta este implicit in coltul stanga sus -> comportament neasteptat la rotire
    updateSpritePosition();

    if (!bulletTexture.loadFromFile("assets/images/bullet.png")) {
        std::cerr << "Failed to load bullet texture!" << std::endl;
    }

	healthBarBackground.setSize(sf::Vector2f(healthBarWidth, healthBarHeight));
	healthBarBackground.setFillColor(sf::Color(97, 27, 14));
	healthBarBackground.setPosition(position_ - sf::Vector2f(0.f, 20.f));

	healthBarBackground.setOutlineThickness(2.f);
	healthBarBackground.setOutlineColor(sf::Color::Black);

	healthBar.setSize(sf::Vector2f(healthBarWidth, healthBarHeight));
	healthBar.setFillColor(sf::Color(14, 97, 29));
	healthBar.setPosition(position_ - sf::Vector2f(0.f, 20.f));
}

void Player::selectWeapon(const int index) {
	if (weapons.empty()) {
		throw PlayerException("No weapons available in inventory");
	}

	if (index < 0) {
		throw PlayerException("Invalid weapon index: negative value");
	}

	if (index >= static_cast<int>(weapons.size())) {
		throw PlayerException("Weapon index out of range: " + std::to_string(index) +
							" (max: " + std::to_string(weapons.size() - 1) + ")");
	}

	currentWeaponIndex = index;
}

void Player::applyDamageBoost(const float boostMultiplier) {
	if (!damageBoostActive) {
		if (!weapons.empty()) {
			weapons[currentWeaponIndex].applyDamageBoost(boostMultiplier);
		}

		damageBoostActive = true;
		damageBoostClock.restart();
	}
}

void Player::applyHealthBoost(const float boostAmount) {
	health = std::min(health + boostAmount, maxHealth);
	updateHealthBar();
}

void Player::applySpeedBoost(const float boostAmount) {
	if (!speedBoostActive) {
		baseSpeed += boostAmount;

		speed = baseSpeed;
		speedBoostActive = true;
		speedBoostClock.restart();
	}
}

void Player::drawPlayer(sf::RenderWindow& window) const {
    window.draw(playerSprite);
}

void Player::updateSpritePosition() {
	playerSprite.setPosition(position);

	sf::FloatRect spriteBounds = playerSprite.getGlobalBounds();

	float barX = spriteBounds.left + spriteBounds.width / 2.f - healthBarBackground.getSize().x / 2.f;
	float barY = spriteBounds.top - 15.f;

	healthBarBackground.setPosition(barX, barY);
	healthBar.setPosition(barX, barY);
}

void Player::movePlayer(float dx, float dy, const sf::RenderWindow& window) {
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
	isShooting = true;

	if (!slowedByShooting) {
		speed = baseSpeed * slowFactor;
		slowedByShooting = true;
	}

    if (shootingClock.getElapsedTime().asSeconds() >= shootCooldown) {                      // jucatorul are un shooting cooldown pentru a preveni spam-ul
        if (!weapons.empty()) {
            Weapon& currentWeapon = weapons[currentWeaponIndex];

            if (!currentWeapon.shoot())
                currentWeapon.reload();

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
        }
        shootingClock.restart();
    }
}


void Player::drawShooting(sf::RenderWindow &window) const {
    for (const Bullet& bullet : bullets) {
        bullet.drawBullet(window);
    }
}

void Player::processBullets(const float deltaTime, const sf::RenderWindow& window) {
    for (Bullet& bullet : bullets)
        bullet.updateBullet(deltaTime);

    std::vector<Bullet> activeBullets;                                          // vector care contine doar gloantele vizibile pe ecran

    for (const Bullet& bullet : bullets) {
        if (!bullet.isOutOfBounds(window))
            activeBullets.push_back(bullet);
    }
    bullets = std::move(activeBullets);
}

sf::Vector2f Player::getCenterPosition() const {
	return {
		playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2.f,
		playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2.f
	};
}

void Player::takeDamage(const float amount) {
	if (shieldActive)
		return;

	health -= amount;

	if (health < 0.f) {
		health = 0.f;
	}

	updateHealthBar();
}

void Player::applySlowness(const float slowMultiplier, const float slowDuration) {
	if (slowTimeLeft <= 0.f) {
		speed *= slowMultiplier;
		slowTimeLeft = slowDuration;
	}
}

void Player::activateTemporaryShield(float duration) {
	shieldActive = true;
	shieldDuration = duration;
	shieldClock.restart();
}

void Player::deactivateShield() {
	shieldActive = false;
}

void Player::startRegeneration(float totalTicks, float amountPerTick) {
	isRegenActive = true;
	regenTicksRemaining = totalTicks;
	regenAmountPerTick = amountPerTick;
	regenClock.restart();
}

void Player::updateRegeneration() {
	if (isRegenActive && regenTicksRemaining > 0) {
		if (regenClock.getElapsedTime() >= regenInterval) {
			if (health < maxHealthVisual)
				applyHealthBoost(regenAmountPerTick);

			regenTicksRemaining--;
			regenClock.restart();
		}
	}

	if (regenTicksRemaining == 0)
		isRegenActive = false;
}

void Player::updateEffectStatus(float deltaTime) {
	if (!isShooting && slowedByShooting) {
		slowedByShooting = false;
		speed = baseSpeed;
	}
	isShooting = false;

	if (slowTimeLeft > 0.f) {						// incetinirea cauzata de slow effect-ul de la strong zombie
		slowTimeLeft -= deltaTime;
		if (slowTimeLeft <= 0.f) {
			slowTimeLeft = 0.f;
			if (!slowedByShooting)
				speed = normalSpeed;
		}
	}

	if (speedBoostActive && speedBoostClock.getElapsedTime().asSeconds() >= 10.f) {
		baseSpeed = normalSpeed;
		speedBoostActive = false;
	}

	if (damageBoostActive && damageBoostClock.getElapsedTime().asSeconds() >= 10.f) {
		weapons[currentWeaponIndex].resetDamage();
		damageBoostActive = false;
	}

	if (shieldActive && shieldClock.getElapsedTime().asSeconds() >= shieldDuration) {
		deactivateShield();
	}
}

bool Player::isDead() const {
	return health <= 0.f;
}

void Player::clearBullets() {
	bullets.clear();
}

void Player::resetPlayerValues() {
	health = 100;
	position = {0.f, 0.f};
	speed = normalSpeed;
}

void Player::updateHealthBar() {
	float healthToDisplay = std::min(health, maxHealthVisual);
	healthBar.setSize(sf::Vector2f(healthBarWidth * (healthToDisplay / maxHealthVisual), healthBarHeight));				// pentru a limita vizual bara de HP
}

void Player::drawHealthBar(sf::RenderWindow& window) const {
	window.draw(healthBarBackground);
	window.draw(healthBar);
}

float Player::getHealth() const { return health; }

sf::Vector2f Player::getPosition() const {
	return playerSprite.getPosition();
}

std::vector<Bullet>& Player::getBullets() { return bullets; }

const Weapon& Player::getCurrentWeapon() const {
	return weapons[currentWeaponIndex];
}

sf::Vector2f Player::getPlayerSize() const { return playerSprite.getGlobalBounds().getSize(); }

sf::Sprite Player::getSprite() const {
	return playerSprite;
}

std::vector<Weapon*> Player::getWeapons() {
	std::vector<Weapon*> weaponPtr;

	for (auto& weapon : weapons)
		weaponPtr.push_back(&weapon);

	return weaponPtr;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << "Player - Health = " << player.health << '\n'
	   << "Speed = " << player.speed << '\n'
	   << player.weapons[player.currentWeaponIndex] << '\n';
	return os;
}
