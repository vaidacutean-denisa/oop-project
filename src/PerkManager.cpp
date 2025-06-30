//
// Created by vaidacutean-denisa on 6/20/25.
//

#include "../headers/PerkManager.h"
#include <random>

#include "../headers/RegenerationDecorator.h"
#include "../headers/MessageDisplay.h"
#include "../headers/ShieldDecorator.h"

PerkManager::PerkManager(AssetsManager& assetsManager_) : enemiesKilled(0), perkSpawnThreshold(3), assetsManager(assetsManager_) {}

void PerkManager::spawnPerk(const sf::Vector2u& windowSize) {
	std::random_device rd;
	std::mt19937 gen(rd());

	const auto windowWidth = static_cast<float>(windowSize.x);
	const auto windowHeight = static_cast<float>(windowSize.y);

	std::uniform_real_distribution dx(100.f, windowWidth - 100.f);
	std::uniform_real_distribution dy(100.f, windowHeight - 100.f);

	const std::vector<std::string> perkTypes = {"health", "speed", "damage"};

	std::uniform_int_distribution type(0, static_cast<int>(perkTypes.size()) - 1);

	std::string randomType = perkTypes[type(gen)];

	sf::Vector2f randomPos(dx(gen), dy(gen));
	sf::Texture& texture = assetsManager.getTexture(randomType + "Perk");

	std::unique_ptr<BasePerk> perk = std::make_unique<Perks>(randomPos, randomType, texture);

	std::uniform_int_distribution chanceDecorator(0, 1);

	if (randomType == "health" && chanceDecorator(gen) == 1) {
		sf::Texture& shieldTexture = assetsManager.getTexture("shieldPerk");
		perk = std::make_unique<ShieldDecorator>(std::move(perk), shieldTexture);
	}
	else if (randomType == "speed" && chanceDecorator(gen) == 1) {
		perk = std::make_unique<RegenerationDecorator>(std::move(perk));
	}

	perks.push_back(std::move(perk));
}

void PerkManager::update(Player& player, const MessageManager& messageManager, MessageDisplay& messageDisplay, const sf::RenderWindow& window) {
	const auto playerBounds = player.getSprite().getGlobalBounds();

	for (auto it = perks.begin(); it != perks.end();) {
		if (playerBounds.intersects((*it)->getBounds())) {
			(*it)->applyPerk(player, messageManager, messageDisplay, window);
			it = perks.erase(it);															// elimina perk-ul dupa ce e activat
		}
		else {
			++it;
		}
	}
}

void PerkManager::draw(sf::RenderWindow& window) const {
	for (const auto& perk : perks) {
		perk->draw(window);
	}
}

void PerkManager::onEnemyKilled(const sf::Vector2u& windowSize) {
	enemiesKilled++;

	if (enemiesKilled >= perkSpawnThreshold) {												// se spawneaza un perk random la fiecare 5 inamici eliminati
		spawnPerk(windowSize);
		enemiesKilled = 0;
	}
}

void PerkManager::reset() {
	enemiesKilled = 0;
	perks.clear();
}