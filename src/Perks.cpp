#include "../headers/Perks.h"

Perks::Perks(sf::Vector2f position_, std::string type_, const sf::Texture& texture)
	: position(position_), type(std::move(type_)) {
	perkSprite.setTexture(texture);
	perkSprite.setPosition(position);
	perkSprite.setScale(4.f, 4.f);

	const sf::FloatRect bounds = perkSprite.getLocalBounds();
	perkSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Perks::applyPerk(Player& player, const MessageManager& messageManager, MessageDisplay& messageDisplay, const sf::RenderWindow& window) const {
	if (!decoratorMessage()) {
		std::string message;
		const float messageDuration = 3.f;
		const float messageCustomY = 45.f;

		if (type == "health") {
			player.applyHealthBoost(20);
			float hp = player.getHealth();

			if (hp > 75)
				message = messageManager.getEventMessage("perk_highHP");
			else if (hp > 35)
				message = messageManager.getEventMessage("perk_midHP");
			else
				message = messageManager.getEventMessage("perk_lowHP");

			messageDisplay.displayMessage(message, messageDuration, window, messageCustomY);
		}
		else if (type == "speed") {
			player.applySpeedBoost(4.5f);
			message = messageManager.getEventMessage("perk_speed");
			messageDisplay.displayMessage(message, messageDuration, window, messageCustomY);
		}
		else if (type == "damage") {
			player.applyDamageBoost(1.5f);
			message = messageManager.getEventMessage("perk_damage");
			messageDisplay.displayMessage(message, messageDuration, window, messageCustomY);
		}
		else {
			message = messageManager.getEventMessage("default");
			messageDisplay.displayMessage(message, messageDuration, window, messageCustomY);
		}
	}
}
void Perks::draw(sf::RenderWindow& window) const {
	window.draw(perkSprite);
}

sf::FloatRect Perks::getBounds() const {
	return perkSprite.getGlobalBounds();
}
