#ifndef SKELETON_H
#define SKELETON_H
#include "../headers/AssetsManager.h"
#include "../headers/Bullet.h"
#include "../headers/Enemy.h"

class Skeleton : public Enemy {
	float collisionDamage;
	std::vector<Bullet> projectiles;
	const sf::Texture& projectileTexture;

	float shootingCooldown;
	float shootTimer;
	float projectileSpeed;
	float projectileDamage;

public:
	// constructors
	Skeleton(const sf::Texture &skeletonTexture, const sf::Texture &projectileTexture_);
	Skeleton(const Skeleton &other);

	Enemy * clone() const override {
		return new Skeleton(*this);
	}

	float getMinDistanceToPlayer(const sf::Vector2f &playerSize) override;
	void updateEnemies(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) override;
	void attackPlayer(Player& player) override;

	void processProjectiles(float deltaTime, const sf::RenderWindow &window, Player& player);
	void drawProjectiles(sf::RenderWindow& window) const;

	void drawImplementation(sf::RenderWindow& window) const override;
};

#endif //SKELETON_H
