#include "../headers/EnemySpawner.h"
#include "../headers/WeakZombie.h"
#include "../headers/StrongZombie.h"
#include "../headers/Skeleton.h"

EnemySpawner::EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies_, float spawnInterval_, AssetsManager& assetsManager_)
	: enemies(enemies_), spawnInterval(spawnInterval_), assetsManager(assetsManager_) {
	std::random_device rd;
	generator.seed(rd());

	if (!assetsManager.loadTexture("weakZombie", "assets/images/weakZombie.png")) {
		std::cout << "Error loading weak zombie texture.\n";
	}

	if (!assetsManager.loadTexture("strongZombie", "assets/images/strongZombie.png")) {
		std::cout << "Error loading strong zombie texture.\n";
	}

	if (!assetsManager.loadTexture("skeleton", "assets/images/skeleton2.png")) {
		std::cout << "Error loading skeleton texture.\n";
	}

	if (!assetsManager.loadTexture("skeleton_projectile", "assets/images/skely_projectile2.png")) {
		std::cout << "Error loading skeleton projectile texture.\n";
	}

	weakZombieTexture = assetsManager.getTexture("weakZombie");
	strongZombieTexture = assetsManager.getTexture("strongZombie");
	skeletonTexture = assetsManager.getTexture("skeleton");
	skeletonProjectileTexture = assetsManager.getTexture("skeleton_projectile");
}

void EnemySpawner::update(const int currentLevel, const sf::RenderWindow& window) {
	if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
		spawnClock.restart();

		spawnInterval = std::max(1.f, 7.f - static_cast<float>(currentLevel) * 0.5f);

		const sf::Vector2u windowSize = window.getSize();
		const auto windowWidth = static_cast<int>(windowSize.x);
		const auto windowHeight = static_cast<int>(windowSize.y);

		std::uniform_int_distribution<int> distX(0, windowWidth - 1);
		std::uniform_int_distribution<int> distY(0, windowHeight - 1);

	    int currentLvlInt = static_cast<int>(currentLevel);
		unsigned int option = 0;

		switch (currentLvlInt) {
			case 1:
				enemies->push_back(std::make_unique<WeakZombie>(assetsManager.getTexture("weakZombie")));
				break;
			case 2:
				option = generator() % 2;
				if (option == 0)
					enemies->push_back(std::make_unique<WeakZombie>(assetsManager.getTexture("weakZombie")));
				else
					enemies->push_back(std::make_unique<StrongZombie>(assetsManager.getTexture("strongZombie")));
				break;

			case 3:
				option = generator() % 3;
				if (option == 0)
					enemies->push_back(std::make_unique<WeakZombie>(assetsManager.getTexture("weakZombie")));

				else if (option == 1)
					enemies->push_back(std::make_unique<StrongZombie>(assetsManager.getTexture("strongZombie")));
				else
				enemies->push_back(std::make_unique<Skeleton>(assetsManager.getTexture("skeleton"),
						assetsManager.getTexture("skeleton_projectile")));
				break;
			default:
				std::cout << "Unknown level.\n";
				break;
		}

		const auto& enemy = enemies->back();
	    auto x = static_cast<float>(distX(generator));
	    auto y = static_cast<float>(distY(generator));

		enemy->setPosition({x, y});
	}
}