#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>
#include "SFML/Audio/Music.hpp"

#include <random>

class Ammunition {
    std::string type;           // tipul munitiei
    int quantity;               // ar trebui sa fie cantitatea pe care o are player-ul in inventar (inexistent din pacate)

public:
    // constructors
    Ammunition(std::string type_, int quantity_);

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Ammunition& ammo) {
        os << "Ammo type = " << ammo.type << '\n'
           << "Quantity = " << ammo.quantity << "\n";
        return os;
    }
};

Ammunition::Ammunition(std::string  type_, int quantity_)
    : type(std::move(type_)), quantity(quantity_) { }

class Weapon {
    std::string name;
    float damage;
    float reloadTime;               // concept doar teoretic so far
    float ammoCapacity;             // capacitatea incarcatorului
    float currentAmmo;              // cate gloante are pe incarcator
    Ammunition ammo;                // tipul de gloante folosite

public:
    // constructors (initialization & cc)
    Weapon(std::string  name_, float dmg_, float rTime_, float capacity_, float currentAmmo_, Ammunition  ammo_);
    Weapon(const Weapon& other) = default;

    // destructor
    ~Weapon() = default;

    // op=
    Weapon& operator=(const Weapon& other);

    // methods
    [[maybe_unused]] void applyDamageBoost(float boostMultiplier);
    // [[maybe_unused]] bool shoot();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Weapon: " << weapon.name <<'\n'
           << "Damage = " << weapon.damage << '\n'
           << "Reload time = " << weapon.reloadTime << '\n'
           << "Ammo capacity = " << weapon.ammoCapacity << '\n'
           << "Current ammo = " << weapon.currentAmmo << '\n'
           << weapon.ammo << '\n';
        return os;
    }

    // getters & setters
    [[nodiscard]] float getDamage() const { return damage; }
    [[nodiscard]] const std::string& getWeaponName() const { return name; }
};

Weapon::Weapon(std::string  name_, float dmg_, float rTime_, float capacity_, float currentAmmo_, Ammunition  ammo_)
    : name(std::move(name_)), damage(dmg_), reloadTime(rTime_), ammoCapacity(capacity_), currentAmmo(currentAmmo_), ammo(std::move(ammo_)) {}

// Weapon::Weapon(const Weapon& other) : name(other.name), damage(other.damage), reloadTime(other.reloadTime),
//                                         ammoCapacity(other.ammoCapacity), currentAmmo(other.currentAmmo), ammo(other.ammo)
// {
//     // std::cout << "constructor de copiere apelat (weapon)\n";
// }

Weapon& Weapon::operator=(const Weapon& other) {
    if (this != &other) {
        name = other.name;
        damage = other.damage;
        reloadTime = other.reloadTime;
        ammoCapacity = other.ammoCapacity;
        currentAmmo = other.currentAmmo;
        ammo = other.ammo;
    }
    return *this;
}

// Weapon::~Weapon() {
//     std::cout << name << " shattered into a thousand pieces, its purpose fulfilled. (destructor weapon)\n";
// }

void Weapon::applyDamageBoost(float boostMultiplier) {
    damage = damage * boostMultiplier;
    std::cout << "Weapon damage boosted by x" << boostMultiplier <<" - time to show your enemies who's in charge.\n";
    std::cout << "The updated damage is: " << damage << '\n';
}

// bool Weapon::shoot() {
//     if (currentAmmo > 0) {
//         currentAmmo--;
//         return true;
//     }                                                                           // de implementat si mecanismul de reload
//
//     std::cout << "Empty magazine. You're on your own now.";
//     return false;
// }

class Player {
    int health;
    float speed;
    sf::Vector2f position;
    std::vector<Weapon> weapons;
    int currentWeaponIndex;
    sf::Sprite playerSprite;

public:
    // constructors
    Player(int health_, float speed_, sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_);

    // methods
    void selectWeapon(int index);

    void applyDamageBoost(float boostMultiplier);
    void applyHealthBoost(int boostAmount);
    void applySpeedBoost(float boostAmount);

    void drawPlayer(sf::RenderWindow& window) const;
    void updateSpritePosition();
    void movePlayer(float dx, float dy);
    void rotatePlayer(float angle);

    // getters & setters
    [[nodiscard]] int getHealth() const { return health; }

    // [[nodiscard]] const Weapon& getWeapon() const {
    //     return weapons[currentWeaponIndex];
    // }

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Player - Health = " << player.health << '\n'
           << "Speed = " << player.speed << '\n'
           << player.weapons[player.currentWeaponIndex] << '\n';
        return os;
    }
};

Player::Player(int health_, float speed_, sf::Vector2f position_, const std::vector<Weapon>& weapons_, const sf::Texture& playerTexture_)
    : health(health_), speed(speed_), position(position_), weapons(weapons_), currentWeaponIndex(0) {
    playerSprite.setTexture(playerTexture_);
    playerSprite.setScale(0.7f, 0.7f);
    updateSpritePosition();
}

void Player::selectWeapon(int index) {
    if (!weapons.empty() && index >= 0 && index < static_cast<int>(weapons.size())) {
        currentWeaponIndex = index;
        std::cout << "Selected weapon: " << weapons[currentWeaponIndex].getWeaponName() << '\n';
        std::cout << "Your weapon has a damage of: " << weapons[currentWeaponIndex].getDamage() <<". Great choice!\n";
    }
    else {
        std::cout << "Invalid weapon index!\n";
    }
}

void Player::applyDamageBoost(const float boostMultiplier) {
    if (!weapons.empty()) {
        weapons[currentWeaponIndex].applyDamageBoost(boostMultiplier);
    }
}

void Player::applyHealthBoost(int boostAmount) {
    const int maxHealth = 150;
    if (health < maxHealth)                                                     // suppose maxhealth = 150 (to be reviewed)
        health += boostAmount;
}

void Player::applySpeedBoost(float boostAmount) {
    speed += boostAmount;
}

void Player::drawPlayer(sf::RenderWindow& window) const {
    window.draw(playerSprite);
}

void Player::updateSpritePosition() {
    playerSprite.setPosition(position.x, position.y);
}

void Player::movePlayer(float dx, float dy) {
    position.x += dx * speed;
    position.y += dy * speed;
}

void Player::rotatePlayer(float angle) {
    playerSprite.setRotation(angle);
}
class Enemy {
    float health;
    float speed;
    sf::Vector2f position;
    sf::Sprite enemySprite;
    // const sf::Texture& enemyTexture;

public:
    // constructors (initialization & cc)
    Enemy(float health_, float speed_, const sf::Vector2f& position_); // const sf::Texture& texture_);
    Enemy(const Enemy& other);

    // op=
    Enemy& operator=(const Enemy& other);

    // destructor
    ~Enemy();

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
        os << "Enemy - health = " << enemy.health << '\n'
           << "Speed = " << enemy.speed << '\n';
        return os;
    }

    // methods
    // [[maybe_unused]] void drawEnemies(sf::RenderWindow& window) const;

};

Enemy::Enemy(float health_, float speed_, const sf::Vector2f& position_) //, const sf::Texture& texture_)
    : health(health_), speed(speed_), position(position_) // enemyTexture(texture_)
{
    // enemySprite.setTexture(texture_);
    // enemySprite.setPosition(position_);
}

Enemy::Enemy(const Enemy& other) : health(other.health), speed(other.speed), position(other.position){ // enemyTexture(other.enemyTexture) {
    std::cout << "cc Enemy\n";
    // enemySprite.setPosition(position);
    // enemySprite.setTexture(enemyTexture);
}

Enemy& Enemy::operator=(const Enemy& other) {
    std::cout << "replicating enemies.. a true test of my patience (op=)\n";
    if (this != &other) {
        health = other.health;
        speed = other.speed;
        position = other.position;
        //
        // enemySprite.setPosition(position);
        // enemySprite.setTexture(enemyTexture);
    }
    return *this;
}

Enemy::~Enemy() {
    std::cout << "One step closer to survival.. (destructor enemy)\n";
}

// void Enemy::drawEnemies(sf::RenderWindow& window) const {
//     window.draw(enemySprite);
// }
//
// class EnemyManager {
//     std::vector<Enemy> enemies;
//     // const sf::Texture& enemyTexture;
//     sf::Clock enemySpawnClock;
//     // float spawnInterval;
//
// public:
//     // constructor
//     EnemyManager(std::vector<Enemy> enemies_, const sf::Texture& enemyTexture_); // float spawnInterval_);
//
// //     // methods
// //     [[maybe_unused]] void spawnEnemy(const sf::Vector2f& spawnAreaMin, const sf::Vector2f& spawnAreaMax);
// //     // void enemyMovement();  momentan nu este implementata
// };
//
// EnemyManager::EnemyManager(std::vector<Enemy> enemies_, const sf::Texture& enemyTexture_) //, float spawnInterval_)
//     : enemies(std::move(enemies_)), enemyTexture(enemyTexture_){} //spawnInterval(spawnInterval_) {}

// void EnemyManager::spawnEnemy(const sf::Vector2f& spawnAreaMin, const sf::Vector2f& spawnAreaMax) {             // generarea random a inamicilor
//     static std::random_device randomSeed;
//     static std::mt19937 generator(randomSeed());                                                             // foloseste alg. Mersenne-Twister
//     std::uniform_real_distribution<float> disX(spawnAreaMin.x, spawnAreaMax.x);
//     std::uniform_real_distribution<float> disY(spawnAreaMin.y, spawnAreaMax.y);
//
//     float x = disX(generator);
//     float y = disY(generator);
//
//     enemies.emplace_back(100.0f, 1.5f, sf::Vector2f(x, y), enemyTexture);
// }

// void EnemyManager::enemyMovement() {
//
// }

class Perks {
    float x, y;                     // de inlocuit cu vector pentru pozitie
    float duration;                 // concept doar teoretic so far
    std::string  type;

public:
    // constructors
    Perks(float x_, float y_, float duration_, std::string  type_) : x(x_), y(y_), duration(duration_), type(std::move(type_)) {}

    // methods
    void applyPerk(Player& player) const;

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Perks& perk) {
        os << "Perks - Type: " << perk.type << '\n'
           << "Position: (" << perk.x << ", " << perk.y << ")" << '\n'
           << "Duration: " << perk.duration << " seconds";
        return os;
    }

};

void Perks::applyPerk(Player& player) const {
    if (type == "health") {
        player.applyHealthBoost(20);
        // std::cout << "Health boost applied.\n";
        if (player.getHealth() > 75)
            std::cout << "You're at " << player.getHealth() << " health. You're in good shape!\n";
        else if (player.getHealth() > 35)
            std::cout << "You've got " << player.getHealth() << " health. Keep pushing!\n";
        else
            std::cout << player.getHealth() << " health left. You're hanging by a thread, but hey, it's a strong thread! Maybe avoid the next hit?\n";
    }
    else if (type == "speed") {
        player.applySpeedBoost(4.5f);
        std::cout << "Speed boost activated. Time to leave everyone in the dust.\n";
    }
    else {
        player.applyDamageBoost(1.5f);
        std::cout << "Your hits just got a bit more.. convincing.\n";
    }
}


// pentru partea de sfml

class Buttons {
    sf::RectangleShape button;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoveredColor;
    sf::Color clickedColor;
    sf::Color outlineColor;
    // float outlineThickness;

public:
    // constructor
    Buttons(sf::Vector2f size, sf::Vector2f position, const std::string& label, const sf::Font& font,
                const sf::Color& idleColor_, const sf::Color& hoveredColor_, const sf::Color& clickedColor_,
                const sf::Color& outlineColor_, float outlineThickness_);

    // methods
    void updateButtonColor(const sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePosition) const;
    void drawButton(sf::RenderWindow& window) const;

    // getter
    std::string getLabel() const { return text.getString(); }

};

Buttons::Buttons(const sf::Vector2f size, const sf::Vector2f position, const std::string& label, const sf::Font& font,
                const sf::Color& idleColor_, const sf::Color& hoveredColor_, const sf::Color& clickedColor_,
                const sf::Color& outlineColor_, float outlineThickness_)
        : idleColor(idleColor_), hoveredColor(hoveredColor_), clickedColor(clickedColor_), outlineColor(outlineColor_)
{
    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(idleColor_);
    button.setOutlineColor(outlineColor_);
    button.setOutlineThickness(outlineThickness_);

    text.setFont(font);
    text.setCharacterSize(26);
    text.setString(label);
    text.setFillColor(sf::Color::Black);
    // text.setOutlineColor(sf::Color::Black);
    // text.setOutlineThickness(2);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(position + size / 2.0f);
}

void Buttons::updateButtonColor(const sf::RenderWindow &window) {
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

    if (button.getGlobalBounds().contains(mousePosition)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            button.setFillColor(clickedColor);
        else
            button.setFillColor(hoveredColor);
    } else
        button.setFillColor(idleColor);
}

bool Buttons::isClicked(sf::Vector2f mousePosition) const {
    if (button.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        }
    }
    return false;
}

void Buttons::drawButton(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(text);
}

class Menu {
    std::vector<Buttons> buttons;
    sf::Font font;

public:
    explicit Menu(const sf::RenderWindow& window);
    void drawMenuButtons(sf::RenderWindow& window);
    std::string handleClick(sf::Vector2i mousePosition) const;
};

Menu::Menu(const sf::RenderWindow& window) {
    if (!font.loadFromFile("SedanSC-Regular.ttf")) {
        std::cerr << "Error loading font.\n";
    }

    sf::Vector2f buttonSize(230.f, 80.f);
    float padding = 40.f;

    std::vector<std::string> labels = {"Play", "Inventory", "Exit"};
    sf::Color idleColor = sf::Color(140, 132, 112);
    sf::Color hoveredColor = sf::Color(160, 150, 120);
    sf::Color clickedColor = sf::Color(100, 90, 70);

    sf::Color outlineColor = sf::Color(97, 88, 71);
    float outlineThickness = 4.f;

    auto labelCount = static_cast<float>(labels.size());
    float totalHeight = labelCount * buttonSize.y + (labelCount - 1) * padding;
    float startY = (static_cast<float>(window.getSize().y) - totalHeight) /2.f;

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Vector2f position((static_cast<float>(window.getSize().x )- buttonSize.x) / 2.f,
            startY + static_cast<float>(i)*(buttonSize.y + padding));
        buttons.emplace_back(buttonSize, position, labels[i], font, idleColor, hoveredColor, clickedColor, outlineColor, outlineThickness);
    }

}

void Menu::drawMenuButtons(sf::RenderWindow& window) {
    for (auto& button : buttons)
        button.updateButtonColor(window);

    for (const auto& button : buttons)
        button.drawButton(window);
}

std::string Menu::handleClick(sf::Vector2i mousePosition) const {
    for (const auto& button : buttons) {
        if (button.isClicked(sf::Vector2f(mousePosition))) {
            return button.getLabel();
        }
    }
    return "";
}

class Game {
    sf::RenderWindow window;
    Menu menu;
    Player& player;
    sf::Music backgroundMusic;
    sf::Text exitMessage;
    sf::Font font;

public:
    explicit Game(Player& player_);
    void runGame();
};

Game::Game(Player& player_) : window(sf::VideoMode({1920, 1080}), "The Last Stand: Undead Uprising", sf::Style::Default),
                            menu(window), player(player_) {
    window.setVerticalSyncEnabled(true);

    if (!backgroundMusic.openFromFile("assets/music/music.mp3")) {
        std::cout << "Error loading background music.\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(20);
    }

    if (!font.loadFromFile("SedanSC-Regular.ttf"))
        std::cerr << "Error loading font.\n";

    exitMessage.setFont(font);
    exitMessage.setCharacterSize(18);
    exitMessage.setString("Press ESC to exit game.");
    exitMessage.setFillColor(sf::Color(140, 132, 112));
    exitMessage.setPosition(845.f, 1020.f);
}

void Game::runGame() {
    sf::Event event{};
    bool gameStarted = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    backgroundMusic.play();

    while (window.isOpen()) {
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
        window.clear(sf::Color(47, 59, 39));

        if (gameStarted) {
            player.drawPlayer(window);

            float dx = 0.0f, dy = 0.0f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                dy = -0.6f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                dx = -0.6f;
                player.rotatePlayer(150.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                dy = 0.6f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                dx = 0.6f;
                player.rotatePlayer(0.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            player.movePlayer(dx, dy);
            player.updateSpritePosition();

        }
        else {
            window.draw(exitMessage);
            menu.drawMenuButtons(window);
        }

        window.display();
    }
    backgroundMusic.stop();
}

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
    if (!playerTexture.loadFromFile("survivor-idle_rifle_0.png")) {
        std::cout << "Error loading player texture.";
    }

    Player player(100, 15.5f, sf::Vector2f(100, 100), {ak, pistol, m4, shotgun}, playerTexture);

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
        std::cout << type << '\n';                      // pentru op<<
        type.applyPerk(player);
    }

    std::cout << "Fully upgraded. Time to paint the town red.\n";
    std::cout << "Player stats after applying perks: \n" << player;

    // in lucru...
    Game game(player);
    game.runGame();
}