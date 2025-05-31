#include "headers/Game.h"
#include "headers/Perks.h"
#include "headers/Player.h"
#include "headers/Ammunition.h"
#include "headers/WeaponManager.h"
#include "headers/GameExceptions.h"

int main() {

    // std::cout << "Commanding Officer to Delta Force:\n" << "Prepare for engagement.\n" << "Select your weapon: [1] - [4].\n"
    //       << "Abort mission? Enter -1. Those unwilling to follow through aren't fit to be part of this unit. Make your choice.\n ";

    // in lucru...
	try {
		WeaponManager weaponManager;
		sf::Texture playerTexture;
		if (!playerTexture.loadFromFile("assets/images/survivor-idle_rifle_0.png"))
			throw ResourceLoadException("survivor-idle_rifle_0.png");

		Player player(100, 16.f, sf::Vector2f(350, 450),
					 weaponManager.createPlayerWeapons(), playerTexture);

		std::vector<Perks> listOfPerks = {                                          // ar putea fi clase derivate? (de revazut) + bonus de ammo crate (idee)
			Perks(6, 14, 0, "health"),
			Perks(4, 3, 10,"speed"),
			Perks(-5, 9, 10, "damage"),                        // de rezolvat cu durata bonusurilor; cel de health nu va avea durata
		};

		// testarea functionalitatii de aplicare a bonusurilor (momentan nu e practica) + voi renunta la ea cand implementez sistemul de aplicare a perk-urilor
		std::cout << "The groundwork is laid. Time to start building something legendary.\n";
		// std::cout << "Player stats before applying perks: \n" << player;
		//
		// std::cout << "Applying perks..\n";
		// for (const Perks& type : listOfPerks) {                                           // parcurge lista de perks si le aplica asupra player-ului
		// 	std::cout << type << '\n';
		// 	// type.applyPerk(player);
		// }

		// std::cout << "Fully upgraded. Time to paint the town red.\n";
		// std::cout << "Player stats after applying perks: \n" << player;

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
