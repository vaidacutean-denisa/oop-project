//
// Created by vaidacutean-denisa on 6/21/25.
//

#include "../headers/ShieldDecorator.h"

ShieldDecorator::ShieldDecorator(std::unique_ptr<BasePerk> perk, const sf::Texture& shieldTexture) : PerkDecorator(std::move(perk)) {
	shieldSprite.setTexture(shieldTexture);
	shieldSprite.setPosition(wrappedPerk->getBounds().left, wrappedPerk->getBounds().top);
	shieldSprite.setScale(0.3f, 0.3f);
}

void ShieldDecorator::applyPerk(Player &player, const MessageManager &messageManager, MessageDisplay &messageDisplay, const sf::RenderWindow &window) const {
	PerkDecorator::applyPerk(player, messageManager, messageDisplay, window);

	player.activateTemporaryShield(15.f);
}

void ShieldDecorator::draw(sf::RenderWindow &window) const {
	window.draw(shieldSprite);
}
