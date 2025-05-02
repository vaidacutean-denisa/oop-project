#include "headers/Enemy.h"
#include "headers/Game.h"
#include "headers/Perks.h"
#include "headers/Player.h"

int main() {
    Ammunition ak_Ammo = Ammunition("7.62mm", 60);
    Ammunition pistol_Ammo = Ammunition("5.56mm", 30);
    Ammunition m4_Ammo = Ammunition("9mm", 60);
    Ammunition shotgun_Ammo = Ammunition("12 Gauge", 20);

    Weapon ak("AK-47", 17, 2.5f, 30, 30, ak_Ammo);
    Weapon pistol("Pistol", 7.0f, 1.3f, 15, 15, pistol_Ammo);
    Weapon m4("M416", 14.5f, 1.8f, 30, 30, m4_Ammo);
    Weapon shotgun("Shotgun", 40, 5.5f, 5, 5, shotgun_Ammo);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/images/survivor-idle_rifle_0.png")) {
        std::cout << "Error loading player texture.";
    }

    Player player(100, 14.f, sf::Vector2f(350, 450), {ak, pistol, m4, shotgun}, playerTexture);

    std::vector<Perks> listOfPerks = {                                          // ar putea fi clase derivate? (de revazut) + bonus de ammo crate (idee)
        Perks(6, 14, 0, "health"),
        Perks(4, 3, 10,"speed"),
        Perks(-5, 9, 10, "damage"),                        // de rezolvat cu durata bonusurilor; cel de health nu va avea durata
    };

    int weaponIndex = 0;
    bool validInput = false;

    std::string input;

    std::cout << "Commanding Officer to Delta Force:\n" << "Prepare for engagement.\n" << "Select your weapon: [1] - [4].\n"
          << "Abort mission? Enter -1. Those unwilling to follow through aren't fit to be part of this unit. Make your choice.\n ";

    while (!validInput) {
        std::cin >> input;

        bool isValid = true;
        bool isNegative = false;

        for (size_t i = 0; i < input.length(); ++i) {
            char ch = input[i];
            if (!std::isdigit(ch)) {
                if (ch == '-' && !isNegative && i == 0)
                    isNegative = true;
                else {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) {
            weaponIndex = std::stoi(input);
            if (weaponIndex >= 1 && weaponIndex <= 4) {
                validInput = true;
            }
            else if (weaponIndex == -1) {
                std::cout << "Quitting.\n";
                return 0;
            }
            else {
                std::cout << "Selection not recognized. Choose a weapon between [1] and [4] to proceed with the mission, or -1 to withdraw.\n";
            }
        }
        else
            std::cout << "Invalid entry. This unit does not operate on guesswork.\n";
    }

    weaponIndex--;
    player.selectWeapon(weaponIndex);

    // testarea functionalitatii de aplicare a bonusurilor (momentan nu e practica)
    std::cout << "The groundwork is laid. Time to start building something legendary.\n";
    std::cout << "Player stats before applying perks: \n" << player;

    std::cout << "Applying perks..\n";
    for (const Perks& type : listOfPerks) {                                           // parcurge lista de perks si le aplica asupra player-ului
        std::cout << type << '\n';
        type.applyPerk(player);
    }

    std::cout << "Fully upgraded. Time to paint the town red.\n";
    std::cout << "Player stats after applying perks: \n" << player;

    // in lucru...
    Game game(player);
    game.runGame();
}