#ifndef MESSAGEDISPLAY_H
#define MESSAGEDISPLAY_H

#include <SFML/Graphics.hpp>
#include "../headers/AssetsManager.h"

class MessageDisplay {
	sf::RectangleShape background;
	sf::Text message;
	sf::Font font;
	sf::Clock timer;
	float displayDuration;
	bool active;

public:
	MessageDisplay();

	void displayMessage(const std::string& message_, float displayDuration_, const sf::RenderWindow& window, const float customY);
	void updateMessage();
	void clearMessage();

	void drawMessage(sf::RenderWindow& window) const;
	// bool isActive() const;
};

#endif //MESSAGEDISPLAY_H
