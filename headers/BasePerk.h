//
// Created by vaidacutean-denisa on 6/21/25.
//

#ifndef BASEPERK_H
#define BASEPERK_H

#include "../headers/Player.h"
#include "../headers/MessageManager.h"
#include "../headers/MessageDisplay.h"

class BasePerk {
public:
	virtual ~BasePerk() = default;

	virtual void applyPerk(Player& player, const MessageManager& messageManager, MessageDisplay& messageDisplay, const sf::RenderWindow& window) const = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;
	virtual bool decoratorMessage() const { return false; }

	[[nodiscard]] virtual sf::FloatRect getBounds() const = 0;
};


#endif //BASEPERK_H
