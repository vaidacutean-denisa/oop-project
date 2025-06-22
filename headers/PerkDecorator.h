//
// Created by vaidacutean-denisa on 6/21/25.
//

#ifndef PERKDECORATOR_H
#define PERKDECORATOR_H

#include "../headers/BasePerk.h"

class PerkDecorator : public BasePerk {
protected:
	std::unique_ptr<BasePerk> wrappedPerk;

public:
	explicit PerkDecorator(std::unique_ptr<BasePerk> perk) : wrappedPerk(std::move(perk)) {}

	void applyPerk(Player& player, const MessageManager& messageManager, MessageDisplay& messageDisplay, const sf::RenderWindow& window) const override;
	void draw(sf::RenderWindow& window) const override;

	sf::FloatRect getBounds() const override;
};

#endif //PERKDECORATOR_H
