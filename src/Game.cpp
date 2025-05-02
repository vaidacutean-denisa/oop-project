#include "Game.h"

Game::Game(Player& player_) : window(sf::VideoMode({1920, 1200}), "The Last Stand: Undead Uprising", sf::Style::Default),
                            menu(window), player(player_), gameStarted(false) {
    window.setVerticalSyncEnabled(true);

    if (!backgroundMusic.openFromFile("assets/music/music.mp3")) {
        std::cout << "Error loading background music.\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(20);
    }

    if (!font.loadFromFile("assets/fonts/SedanSC-Regular.ttf"))
        std::cerr << "Error loading font.\n";

    exitMessage.setFont(font);
    exitMessage.setCharacterSize(18);
    exitMessage.setString("Press ESC to exit game.");
    exitMessage.setFillColor(sf::Color(140, 132, 112));

    const sf::FloatRect textBounds = exitMessage.getLocalBounds();
    exitMessage.setOrigin(textBounds.left + textBounds.width / 2.f, 0);
    exitMessage.setPosition(static_cast<float>(window.getSize().x) / 2.f, 1080);
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
                gameStarted = true;
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

void Game::updateGame(const float deltaTime) const {
    if (gameStarted) {
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
    }
}

void Game::drawGame() {
    player.drawShooting(window);
}

void Game::drawMenu() {
    window.draw(exitMessage);
    menu.drawMenuButtons(window);
}

void Game::runGame() {
    backgroundMusic.play();

    while (window.isOpen()) {
        handleInput();
        window.clear(sf::Color(47, 59, 39));

        float deltaTime = clock.restart().asSeconds();

        updateGame(deltaTime);

        if (gameStarted) {
            drawGame();
            player.drawPlayer(window);
        }
        else
            drawMenu();

        handleMusic();

        window.display();
    }

    backgroundMusic.stop();
}