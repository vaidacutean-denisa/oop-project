#ifndef PERKS_H
#define PERKS_H

#include <string>
#include "../headers/MessageDisplay.h"
#include "../headers/MessageManager.h"
#include "../headers/Player.h"
#include "../headers/BasePerk.h"

class Perks : public BasePerk {
	sf::Vector2f position;
    std::string type;
	sf::Sprite perkSprite;

public:
    // constructors
    Perks(sf::Vector2f position_, std::string type_, const sf::Texture& texture_);

    // methods
	void applyPerk(Player &player, const MessageManager &messageManager, MessageDisplay &messageDisplay, const sf::RenderWindow &window) const override;
	void draw(sf::RenderWindow& window) const override;
	bool decoratorMessage() const override;

	sf::FloatRect getBounds() const override;
};


#endif //PERKS_H
