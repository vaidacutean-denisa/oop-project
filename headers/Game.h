#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Player.h"
#include "SFML/Audio/Music.hpp"

class Game {
	sf::RenderWindow window;
	Menu menu;
	Player& player;
	sf::Clock clock;
	sf::Music backgroundMusic;
	sf::Text exitMessage;
	sf::Font font;
	bool gameStarted;

	void handleMusic();
	void handleInput();
	void updateGame(float deltaTime) const;
	void drawGame();
	void drawMenu();

public:
	explicit Game(Player& player_);
	void runGame();
};


#endif //GAME_H
