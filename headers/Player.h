#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Bullet.h"
#include <memory>

class Player {
    float health;
	float maxHealthVisual;
	float maxHealth;															// cu perks poate ajunge la 150hp, dar bara de hp sa ramana la 100 practic

	sf::RectangleShape healthBarBackground;
	sf::RectangleShape healthBar;
	float healthBarWidth = 100.f;
	float healthBarHeight = 10.f;

    float speed;
    float normalSpeed;                                                          // pentru a reveni la viteza normala dupa ce trage
	float baseSpeed;

	sf::Vector2f position;

    int currentWeaponIndex;
    std::vector<Weapon> weapons;
    std::vector<Bullet> bullets;
    sf::Texture bulletTexture;

    sf::Sprite playerSprite;

    sf::Clock shootingClock;
    float shootCooldown;
    sf::Clock slowTimer;                                                        // viteza jucatorului scade atunci cand trage cu arma
    float slowFactor;
	bool slowedByShooting;

	float slowTimeLeft = 0.f;
	bool isShooting = false;

	sf::Clock speedBoostClock;
	bool speedBoostActive = false;

	sf::Clock damageBoostClock;
	bool damageBoostActive = false;

	bool shieldActive = false;
	float shieldDuration;
	sf::Clock shieldClock;

	sf::Clock regenClock;														// pentru regeneration (perk)
	sf::Time regenInterval = sf::seconds(0.5f);							// la cate secunde se aplica regenerarea
	bool isRegenActive = false;
	float regenTicksRemaining = 0;					    				    	// de cate ori se aplica regenerarea
	float regenAmountPerTick = 0;									    		// cat HP se aplica la fiecare regenerare

public:
    // constructors
    Player(float health_, float speed_, sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_);

    // methods
    void selectWeapon(int index);

    void applyDamageBoost(float boostMultiplier);
    void applyHealthBoost(float boostAmount);
    void applySpeedBoost(float boostAmount);

    void drawPlayer(sf::RenderWindow& window) const;
    void updateSpritePosition();

    void movePlayer(float dx, float dy, const sf::RenderWindow& window);
    void rotatePlayer(float angle);

    void shoot();
    void drawShooting(sf::RenderWindow& window) const;
    void processBullets(float deltaTime, const sf::RenderWindow &window);
	sf::Vector2f getCenterPosition() const;

	void takeDamage(float amount);
	void applySlowness(const float slowMultiplier, const float slowDuration);

	void activateTemporaryShield(float duration);
	void deactivateShield();
	bool isShieldActive() const;

	void startRegeneration(float totalTicks, float amountPerTick);
	void updateRegeneration();

	void updateEffectStatus(float deltaTime);

	bool isDead() const;

	void clearBullets();
	void resetPlayerValues();

	void updateHealthBar();
	void drawHealthBar(sf::RenderWindow& window) const;

	// getters & setters
    float getHealth() const;
    sf::Vector2f getPosition() const;
    std::vector<Bullet>& getBullets();
    const Weapon& getCurrentWeapon() const;
	sf::Vector2f getPlayerSize() const;
	sf::Sprite getSprite() const;
	std::vector<Weapon *> getWeapons();

	// op <<
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif //PLAYER_H
