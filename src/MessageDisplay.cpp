#include "MessageDisplay.h"

#include <iostream>

MessageDisplay::MessageDisplay() : displayDuration(0), active(false) {
	if (!font.loadFromFile("assets/fonts/BlackOpsOne-Regular.ttf")) {
		std::cerr << "Error loading font.\n";
	}
	message.setFont(font);
	message.setCharacterSize(20);
	message.setFillColor(sf::Color(50, 40, 38));
	message.setLetterSpacing(1.7f);

	background.setSize(sf::Vector2f(500.f, 100.f));
	background.setFillColor(sf::Color(140, 125, 105, 210));
	background.setOutlineColor(sf::Color(95, 85, 70));
	background.setOutlineThickness(4.f);
}

void MessageDisplay::displayMessage(std::string& message_, float displayDuration_, const sf::RenderWindow& window) {
	message.setString(message_);
	displayDuration = displayDuration_;
	timer.restart();
	active = true;

	const sf::FloatRect textBounds = message.getLocalBounds();
	constexpr float padding = 30.f;
	const auto windowWidth = static_cast<float>(window.getSize().x);
	const auto windowHeight = static_cast<float>(window.getSize().y);

	background.setSize(sf::Vector2f(textBounds.width + padding, textBounds.height + padding));
	background.setOrigin(0.f, 0.f);

	const float backgroundX = (windowWidth - background.getSize().x) / 2.f;
	const float backgroundY = windowHeight - background.getSize().y - 45.f;

	background.setPosition(backgroundX, backgroundY);

	message.setOrigin(textBounds.left + textBounds.width / 2.f,
	                  textBounds.height / 2.f - textBounds.top);

	message.setPosition(backgroundX + background.getSize().x / 2.f,
						backgroundY + background.getSize().y / 2.f);
}

void MessageDisplay::updateMessage() {
	if (active && timer.getElapsedTime().asSeconds() >= displayDuration)
		active = false;
}

void MessageDisplay::drawMessage(sf::RenderWindow& window) const {
	if (!active)
		return;

	window.draw(background);
	window.draw(message);
}

bool MessageDisplay::isActive() const {
	return active;
}