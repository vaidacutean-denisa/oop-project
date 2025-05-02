#include "../headers/Menu.h"
#include <iostream>

Menu::Menu(const sf::RenderWindow& window) {
	if (!font.loadFromFile("assets/fonts/SedanSC-Regular.ttf")) {
		std::cerr << "Error loading font.\n";
	}

	sf::Vector2f buttonSize(230.f, 80.f);
	float padding = 40.f;

	std::vector<std::string> labels = {"Play", "Inventory", "Exit"};
	sf::Color idleColor = sf::Color(140, 132, 112);
	sf::Color hoveredColor = sf::Color(160, 150, 120);
	sf::Color clickedColor = sf::Color(100, 90, 70);

	sf::Color outlineColor = sf::Color(97, 88, 71);
	float outlineThickness = 4.f;

	auto labelCount = static_cast<float>(labels.size());
	float totalHeight = labelCount * buttonSize.y + (labelCount - 1) * padding;
	float startY = (static_cast<float>(window.getSize().y) - totalHeight) /2.f;

	for (size_t i = 0; i < labels.size(); ++i) {
		float windowWidth = static_cast<float>(window.getSize().x);

		sf::Vector2f position((windowWidth- buttonSize.x) / 2.f, startY + static_cast<float>(i)*(buttonSize.y + padding));
		menuButtons.emplace_back(buttonSize, position, labels[i], font, idleColor, hoveredColor, clickedColor,
								 outlineColor, outlineThickness);
	}
}

void Menu::drawMenuButtons(sf::RenderWindow& window) {
	for (auto& button : menuButtons)
		button.updateButtonColor(window);

	for (const auto& button : menuButtons)
		button.drawButton(window);
}

std::string Menu::handleClick(sf::Vector2i mousePosition) const {
	for (const auto& button : menuButtons) {
		if (button.isClicked(sf::Vector2f(mousePosition))) {
			return button.getLabel();
		}
	}
	return "";
}
