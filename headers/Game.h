#ifndef GAME_H
#define GAME_H

#include <SFML/Audio/Music.hpp>
#include "../headers/AssetsManager.h"
#include "../headers/CombatSystem.h"
#include "../headers/EnemySpawner.h"
#include "../headers/LevelManager.h"
#include "../headers/Menu.h"
#include "../headers/Player.h"
#include "../headers/MessageDisplay.h"

enum class GameState {
	Menu,
	GameRunning,
	GameOver,
	GameWin
};

class Game {
	sf::RenderWindow window;
	Menu menu;
	Player& player;
	sf::Clock clock;

    AssetsManager assetsManager;
    sf::Music backgroundMusic;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture battlefieldTexture;
    sf::Sprite battlefieldSprite;

	sf::Text exitMessage;

	std::unique_ptr<EnemySpawner> spawner;
	std::vector<std::unique_ptr<Enemy>> enemies{};

    MessageManager messageManager;
    LevelManager levelManager;
	int previousLevel;

	MessageDisplay messageDisplay;
	int tempFinalLevel = 4;

	bool finalMessageShown;

	GameState gameState;

	void handleMusic();
	void handleInput();

	void updateGame(float deltaTime);
	void updateRunning(float deltaTime);

	void checkEndings();
	void endGame(GameState gameState);

	void drawGame();
	void drawMenu();

public:
	explicit Game(Player& player_);
	void runGame();
	void resetGame();
};


#endif //GAME_H
