#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "../headers/Weapon.h"
#include "../headers/Buttons.h"

class InventoryMenu {
	std::vector<Weapon*> weapons;
	std::vector<sf::RectangleShape> weaponSlots;
	std::vector<sf::Sprite> weaponSprites;
	std::vector<sf::Text> weaponLabels;

	sf::Font font;
	std::vector<Buttons> inventoryButtons;
	sf::RectangleShape background;
	std::map<std::string, sf::Texture> weaponTextures;
	std::vector<sf::Texture> textures;

	// methods
	void loadWeaponTextures();
	void createWeaponSlots();
	void clearContainers();

public:
	// constructor
	explicit InventoryMenu(const std::vector<Weapon*>& playerWeapons);

	// methods
	void drawInventory(sf::RenderWindow& window) const;
	int handleClick(const sf::Vector2f &mousePosition) const;
	void centerInWindow(const sf::RenderWindow &window);

	// getters & setters
	void setPosition(float x, float y);
};

#endif //INVENTORY_H
