#ifndef MENU_H
#define MENU_H

#include "Buttons.h"

class Menu {
	std::vector<Buttons> menuButtons;
	sf::Font font;

public:
	explicit Menu(const sf::RenderWindow& window);
	void drawMenuButtons(sf::RenderWindow& window);
	std::string handleClick(sf::Vector2i mousePosition) const;
};

#endif //MENU_H
