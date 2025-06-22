#include "headers/Game.h"
#include "headers/Perks.h"
#include "headers/Player.h"
#include "headers/Ammunition.h"
#include "headers/WeaponManager.h"
#include "headers/GameExceptions.h"

int main() {
	try {
		WeaponManager weaponManager;
		sf::Texture playerTexture;
		if (!playerTexture.loadFromFile("assets/images/survivor-idle_rifle_0.png"))
			throw ResourceLoadException("survivor-idle_rifle_0.png");

		Player player(100, 16.f, sf::Vector2f(350, 450),
					 weaponManager.createPlayerWeapons(), playerTexture);

		Game game(player);
		game.runGame();
	}
	catch (const ResourceLoadException& e) {
		std::cerr << "Resource Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch (const PlayerException& e) {
		std::cerr << "Player Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch (const GameStateException& e) {
		std::cerr << "Game State Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch (const std::exception& e) {
		std::cerr << "Unexpected error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
