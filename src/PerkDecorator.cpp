//
// Created by vaidacutean-denisa on 6/21/25.
//

#include "../headers/PerkDecorator.h"

void PerkDecorator::applyPerk(Player& player, const MessageManager& messageManager, MessageDisplay& messageDisplay, const sf::RenderWindow& window) const  {
	if (wrappedPerk)
		wrappedPerk->applyPerk(player, messageManager, messageDisplay, window);
	else
		throw std::runtime_error("WrappedPerk is null.\n");
}

void PerkDecorator::draw(sf::RenderWindow& window) const  {
	wrappedPerk->draw(window);
}

sf::FloatRect PerkDecorator::getBounds() const  {
	return wrappedPerk->getBounds();
}