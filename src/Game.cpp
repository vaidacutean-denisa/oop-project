#include "../headers/Game.h"
#include "../headers/Skeleton.h"

Game::Game(Player& player_) : window(sf::VideoMode({1920, 1200}), "The Last Stand: Undead Uprising", sf::Style::Default),
                            menu(window), player(player_), messageManager(), levelManager(messageManager),
							previousLevel(0), messageDisplay(), gameState(GameState::Menu)
 {
    window.setVerticalSyncEnabled(true);

    if (!assetsManager.loadTexture("background", "assets/images/background2.png")) {
        std::cout << "Error loading background texture.\n";                     // throw aici
    }

    if (!assetsManager.loadTexture("battlefield", "assets/images/battlefield22.png")) {
        std::cout << "Error loading battlefield texture.\n";
    }

    if (!assetsManager.loadFont("font", "assets/fonts/SedanSC-Regular.ttf")) {
        std::cout << "Error loading font.\n";
    }

    backgroundSprite = assetsManager.getScaledSprite("background", window.getSize());
    battlefieldSprite = assetsManager.getScaledSprite("battlefield", window.getSize());

    if (!backgroundMusic.openFromFile("assets/music/music.mp3")) {
        std::cout << "Error loading background music.\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(20);
    }

    font = assetsManager.getFont("font");

    exitMessage.setFont(font);
    exitMessage.setCharacterSize(18);
    exitMessage.setString("Press ESC to exit game.");
    exitMessage.setFillColor(sf::Color(140, 132, 112));

    const sf::FloatRect textBounds = exitMessage.getLocalBounds();
    exitMessage.setOrigin(textBounds.left + textBounds.width / 2.f, 0);
    exitMessage.setPosition(static_cast<float>(window.getSize().x) / 2.f, 1080);

    spawner = std::make_unique<EnemySpawner>(&enemies, 4.f, assetsManager);
	finalMessageShown = false;
}

void Game::handleMusic() {
    const float currentVolume = backgroundMusic.getVolume();
    static bool isMuted = false;

    if (!isMuted) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) && currentVolume < 100) {
            backgroundMusic.setVolume(std::min(currentVolume + 2.f, 100.f));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && currentVolume > 0) {
            backgroundMusic.setVolume(std::max(currentVolume - 2.f, 0.f));
        }
    }

    static bool pressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        if (!pressed) {
            if (backgroundMusic.getStatus() == sf::Music::Playing) {
                backgroundMusic.pause();
                isMuted = true;
            }
            else {
                backgroundMusic.play();
                isMuted = false;
            }
            pressed = true;
        }
    }
    else
        pressed = false;
}

void Game::handleInput() {
    sf::Event event{};

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::string clickedButton = menu.handleClick(sf::Mouse::getPosition(window));

            if (clickedButton == "Play") {
                std::cout << "Play button clicked.\n";
                gameState = GameState::GameRunning;
            }
            if (clickedButton == "Inventory") {
                std::cout << "Inventory button clicked.\n";
            }
            if (clickedButton == "Exit") {
                std::cout << "Exit button clicked.\n";
                window.close();
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void Game::updateGame(const float deltaTime) {
	switch (gameState) {
		case GameState::GameRunning:
			updateRunning(deltaTime);
			break;
		case GameState::GameOver:
		case GameState::GameWin: {
			static bool enterPressed = false;
			checkEndings();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				if (!enterPressed) {
					resetGame();
					enterPressed = true;
				}
			break;
		}
		default:
			break;
	}
}

void Game::updateRunning(const float deltaTime) {
	float dx = 0.f, dy = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.rotatePlayer(270.f);
		dy = -0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.rotatePlayer(180.f);
		dx = -0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.rotatePlayer(90.f);
		dy = 0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.rotatePlayer(0.f);
		dx = 0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		player.shoot();

	player.movePlayer(dx, dy, window);
	player.updateSpritePosition();
	player.processBullets(deltaTime, window);

	levelManager.updateLevel(deltaTime);

	int currentLevel = levelManager.getCurrentLevel();

	if (currentLevel != previousLevel) {
		previousLevel = currentLevel;
		std::string levelMessage = messageManager.getLevelMessage(currentLevel);

		messageDisplay.displayMessage(levelMessage, 5.f, window);
	}
	messageDisplay.updateMessage();

	if (levelManager.getCurrentLevel() == tempFinalLevel) {
		if (enemies.empty() && !player.isDead())
			gameState = GameState::GameWin;
	}

	spawner->update(levelManager.getCurrentLevel(), window);

	sf::Vector2f playerCenter = player.getCenterPosition();
	for (auto& enemy : enemies) {
		enemy->updateEnemies(playerCenter, window.getSize(), player.getPlayerSize());
		enemy->resolveCollision(enemies);
		enemy->attackPlayer(player);

		if (auto* skeleton = dynamic_cast<Skeleton*>(enemy.get())) {
			skeleton->processProjectiles(deltaTime, window, player);
		}
	}

	CombatSystem::handleCombat(player.getBullets(), enemies, player.getCurrentWeapon());

	if (player.isDead())
		endGame(GameState::GameOver);
}

void Game::checkEndings() {
	if (!finalMessageShown) {
		if (player.isDead())
			endGame(GameState::GameOver);
		else if (levelManager.getCurrentLevel() == tempFinalLevel && enemies.empty())
			endGame(GameState::GameWin);
	}
}

void Game::endGame(GameState endState) {
	gameState = endState;

	enemies.clear();
	player.getSprite().setPosition(-1000, -1000);

	std::string endMessage;
	if (endState == GameState::GameWin)
		endMessage = messageManager.getEventMessage("gameWin");
	else
		endMessage = messageManager.getEventMessage("gameOver");

	messageDisplay.displayMessage(endMessage, 7.f, window);
	if (endState == GameState::GameWin) {
		std::string epilogue = messageManager.getEventMessage("epilogue");
		messageDisplay.displayMessage(epilogue, 8.f, window);
	}

	finalMessageShown = true;
	//
	// std::string restartMessage = messageManager.getEventMessage("restart");
	// messageDisplay.displayMessage(restartMessage, 5.f, window);
}

void Game::drawGame() {
    player.drawShooting(window);

    for (const auto& enemy : enemies) {
        enemy->drawEnemies(window);

    	if (const auto skeleton = dynamic_cast<const Skeleton*>(enemy.get()))
    		skeleton->drawProjectiles(window);
    }
	messageDisplay.drawMessage(window);
}

void Game::drawMenu() {
    window.draw(backgroundSprite);
    window.draw(exitMessage);
    menu.drawMenuButtons(window);
}

void Game::runGame() {
    backgroundMusic.play();

	while (window.isOpen()) {
        handleInput();
        window.clear(sf::Color(47, 59, 39));

        float deltaTime = clock.restart().asSeconds();

		if (gameState == GameState::Menu)
			drawMenu();
		else {
			updateGame(deltaTime);
			window.draw(battlefieldSprite);
			drawGame();

			if (gameState == GameState::GameRunning) {
				player.drawPlayer(window);
			}
		}

        handleMusic();

        window.display();
    }

    backgroundMusic.stop();
}

void Game::resetGame() {
	gameState = GameState::Menu;
	finalMessageShown = false;

	levelManager.resetLevel();
	enemies.clear();
	player.resetPlayerValues();
}