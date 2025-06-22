#include "../headers/EnemySpawner.h"
#include "../headers/WeakZombie.h"
#include "../headers/StrongZombie.h"
#include "../headers/Skeleton.h"
#include "../headers/Death.h"

EnemySpawner::EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies_, float spawnInterval_, AssetsManager& assetsManager_)
	: enemies(enemies_), spawnInterval(spawnInterval_), assetsManager(assetsManager_) {
	std::random_device rd;
	generator.seed(rd());

	assetsManager.loadTexture("weakZombie", "assets/images/weakZombie.png");
	assetsManager.loadTexture("strongZombie", "assets/images/strongZombie.png");
	assetsManager.loadTexture("skeleton", "assets/images/skeleton2.png");
	assetsManager.loadTexture("death", "assets/images/death3.png");

	assetsManager.loadTexture("skeleton_projectile", "assets/images/skely_projectile2.png");

	weakZombieTexture = assetsManager.getTexture("weakZombie");
	strongZombieTexture = assetsManager.getTexture("strongZombie");
	skeletonTexture = assetsManager.getTexture("skeleton");
	skeletonProjectileTexture = assetsManager.getTexture("skeleton_projectile");
	deathTexture = assetsManager.getTexture("death");

	weakZombieTemplate = std::make_unique<WeakZombie>(weakZombieTexture);
	strongZombieTemplate = std::make_unique<StrongZombie>(strongZombieTexture);
	skeletonTemplate = std::make_unique<Skeleton>(skeletonTexture, skeletonProjectileTexture);
	deathTemplate = std::make_unique<Death>(deathTexture);
}

void EnemySpawner::update(const int currentLevel, const sf::RenderWindow& window) {
	if (currentLevel > tempFinalLevel && enemies->empty() && !deathSpawned) {
		spawnDeath(window);
		return;
	}

	if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
		spawnClock.restart();

		spawnInterval = std::max(1.f, 5.f - static_cast<float>(currentLevel) * 0.5f);

		const sf::Vector2u windowSize = window.getSize();
		const auto windowWidth = static_cast<int>(windowSize.x);
		const auto windowHeight = static_cast<int>(windowSize.y);

		std::uniform_int_distribution<int> distX(0, windowWidth - 1);
		std::uniform_int_distribution<int> distY(0, windowHeight - 1);

	    int currentLvlInt = currentLevel;
		unsigned int option = 0;

		std::unique_ptr<Enemy> newEnemy;

		switch (currentLvlInt) {
			case 1:
				newEnemy = std::unique_ptr<Enemy>(weakZombieTemplate->clone());
				break;
			case 2:
				option = generator() % 2;
				if (option == 0)
					newEnemy = std::unique_ptr<Enemy>(weakZombieTemplate->clone());
				else
                    newEnemy = std::unique_ptr<Enemy>(strongZombieTemplate->clone());
				break;

			case 3:
			case 4:
				option = generator() % 3;
				if (option == 0)
					newEnemy = std::unique_ptr<Enemy>(weakZombieTemplate->clone());
				else if (option == 1)
					newEnemy = std::unique_ptr<Enemy>(strongZombieTemplate->clone());
				else
					newEnemy = std::unique_ptr<Enemy>(skeletonTemplate->clone());
				break;
			default:
				// std::cout << "Unknown level.\n";
				return;
		}

	    auto x = static_cast<float>(distX(generator));
	    auto y = static_cast<float>(distY(generator));
		newEnemy->setPosition({x, y});

		enemies->push_back(std::move(newEnemy));
	}
}

void EnemySpawner::spawnDeath(const sf::RenderWindow& window) {
	const sf::Vector2u windowSize = window.getSize();
	const auto windowWidth = static_cast<int>(windowSize.x);
	const auto windowHeight = static_cast<int>(windowSize.y);

	std::uniform_int_distribution<int> distX(0, windowWidth - 1);
	std::uniform_int_distribution<int> distY(0, windowHeight - 1);

	auto x = static_cast<float>(distX(generator));
	auto y = static_cast<float>(distY(generator));

	std::unique_ptr<Enemy> deathEnemy = std::unique_ptr<Enemy>(deathTemplate->clone());
	deathEnemy->setPosition({x, y});

	enemies->push_back(std::move(deathEnemy));
	deathSpawned = true;
}

void EnemySpawner::resetDeathSpawn() {
	deathSpawned = false;
}

bool EnemySpawner::isDeathSpawned() const {
	return deathSpawned;
}