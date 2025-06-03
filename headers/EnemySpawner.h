#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <memory>
#include <random>

#include "../headers/Enemy.h"
#include "../headers/AssetsManager.h"

class EnemySpawner {
	std::vector<std::unique_ptr<Enemy>>* enemies;
	sf::Clock spawnClock;
	float spawnInterval;

	sf::Texture weakZombieTexture;
	sf::Texture strongZombieTexture;
	sf::Texture skeletonTexture;
	sf::Texture skeletonProjectileTexture;
	sf::Texture deathTexture;

	std::unique_ptr<Enemy> weakZombieTemplate;
	std::unique_ptr<Enemy> strongZombieTemplate;
	std::unique_ptr<Enemy> skeletonTemplate;
	std::unique_ptr<Enemy> deathTemplate;

	std::mt19937 generator;

	AssetsManager& assetsManager;

	int tempFinalLevel = 4;
	bool deathSpawned = false;

	void spawnDeath(const sf::RenderWindow &window);

public:
	// constructor
	EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies_, float spawnInterval_, AssetsManager& assetsManager_);

	// methods
	void update(int currentLevel, const sf::RenderWindow& window);

	void resetDeathSpawn();

	bool isDeathSpawned() const;

};

#endif //ENEMYSPAWNER_H
