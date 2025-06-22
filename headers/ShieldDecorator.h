//
// Created by vaidacutean-denisa on 6/21/25.
//

#ifndef SHIELDDECORATOR_H
#define SHIELDDECORATOR_H

#include "../headers/PerkDecorator.h"

class ShieldDecorator : public PerkDecorator {
	sf::Sprite shieldSprite;

public:
	// constructor
	ShieldDecorator(std::unique_ptr<BasePerk> perk, const sf::Texture &shieldTexture);

	// methods
	void applyPerk(Player &player, const MessageManager &messageManager, MessageDisplay &messageDisplay, const sf::RenderWindow &window) const override;
	void draw(sf::RenderWindow& window) const override;

	bool decoratorMessage() const override;
};

#endif //SHIELDDECORATOR_H
