//
// Created by vaidacutean-denisa on 6/22/25.
//

#ifndef REGENERATIONDECORATOR_H
#define REGENERATIONDECORATOR_H

#include "../headers/PerkDecorator.h"

class RegenerationDecorator : public PerkDecorator {
public:
	// constructor
	explicit RegenerationDecorator(std::unique_ptr<BasePerk> perk);

	// methods
	void applyPerk(Player &player, const MessageManager &messageManager, MessageDisplay &messageDisplay, const sf::RenderWindow &window) const override;
};


#endif //REGENERATIONDECORATOR_H
