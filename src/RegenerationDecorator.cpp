//
// Created by vaidacutean-denisa on 6/22/25.
//

#include "../headers/RegenerationDecorator.h"

RegenerationDecorator::RegenerationDecorator(std::unique_ptr<BasePerk> perk) : PerkDecorator(std::move(perk)) {}


void RegenerationDecorator::applyPerk(Player& player, const MessageManager& messageManager, MessageDisplay& messageDisplay, const sf::RenderWindow& window) const  {
	PerkDecorator::applyPerk(player, messageManager, messageDisplay, window);

	float regenTotalTicks = 7.f;
	float regenAmountPerTick = 4.f;

	player.startRegeneration(regenTotalTicks, regenAmountPerTick);

	std::string regenMessage = messageManager.getEventMessage("perk_regen");
	messageDisplay.displayMessage(regenMessage, 3.f, window, 45.f);
}
