//
// Created by vaidacutean-denisa on 6/20/25.
//

#ifndef PERKMANAGER_H
#define PERKMANAGER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "MessageDisplay.h"
#include "../headers/Perks.h"
#include "../headers/Player.h"
#include "../headers/MessageManager.h"
#include "../headers/AssetsManager.h"

class PerkManager {
	std::vector<std::unique_ptr<BasePerk>> perks;
	int enemiesKilled;
	int perkSpawnTreshold;

	AssetsManager& assetsManager;

public:
	// constructors
	explicit PerkManager(AssetsManager& assetsManager_);

	// methods
	void spawnPerk(const sf::Vector2u& windowSize);
	void update(Player &player, const MessageManager &messageManager, MessageDisplay &messageDisplay, const sf::RenderWindow &window);
	void draw(sf::RenderWindow& window) const;

	void onEnemyKilled(const sf::Vector2u& windowSize);

	void reset();
};

#endif //PERKMANAGER_H
