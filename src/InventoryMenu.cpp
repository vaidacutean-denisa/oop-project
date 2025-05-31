#include "../headers/InventoryMenu.h"

InventoryMenu::InventoryMenu(const std::vector<Weapon*>& playerWeapons) :weapons(playerWeapons) {
	background.setSize(sf::Vector2f(1000, 750));
	background.setFillColor(sf::Color(140, 125, 105, 180));

	if (!font.loadFromFile("assets/fonts/BlackOpsOne-Regular.ttf"))
		throw std::runtime_error("Failed to load font");

	loadWeaponTextures();
	createWeaponSlots();
}

void InventoryMenu::loadWeaponTextures() {
	std::map<std::string, std::string> textureFiles = {
		{"AK-47", "assets/images/ak47.png"},
		{"Pistol", "assets/images/pistol.png"},
		{"M416", "assets/images/m416.png"},
		{"Shotgun", "assets/images/shotgun.png"}
	};

	for (const auto& [weaponName, filePath] : textureFiles) {
		textures.emplace_back();
		if (textures.back().loadFromFile(filePath))
			weaponTextures[weaponName] = textures.back();
	}
}

void InventoryMenu::createWeaponSlots() {
	clearContainers();

    float boxSize = 250;
    float padding = 70;

    int rows = 2;			// pentru grid 2x2
    int cols = 2;

	float totalWidth = static_cast<float>(cols) * boxSize + static_cast<float>(cols - 1) * padding;
	float totalHeight = static_cast<float>(rows) * boxSize + static_cast<float>(rows - 1) * padding;

    float startX = background.getPosition().x + (background.getSize().x - totalWidth) / 2;
    float startY = background.getPosition().y + (background.getSize().y - totalHeight) / 2;

    for(size_t i = 0; i < weapons.size(); ++i) {
    	int row = static_cast<int>(i) / cols;
    	int col = static_cast<int>(i) % cols;
    	float x = startX + static_cast<float>(col) * (boxSize + padding);
    	float y = startY + static_cast<float>(row) * (boxSize + padding);

        sf::RectangleShape slot;
        slot.setSize(sf::Vector2f(boxSize, boxSize));
        slot.setPosition(x, y);
        slot.setFillColor(sf::Color(100, 90, 80));
        slot.setOutlineColor(sf::Color::Black);
        slot.setOutlineThickness(2);
        weaponSlots.push_back(slot);

        if (weaponTextures.contains(weapons[i]->getWeaponName())) {
            sf::Sprite sprite;
            sprite.setTexture(weaponTextures[weapons[i]->getWeaponName()]);

            float scaleX = boxSize / sprite.getLocalBounds().width;
            float scaleY = boxSize / sprite.getLocalBounds().height;
            float scale = std::min(scaleX, scaleY) * 0.8f;
            sprite.setScale(scale, scale);

            sprite.setPosition(x + (boxSize - sprite.getGlobalBounds().width) / 2,
                               y + (boxSize - sprite.getGlobalBounds().height) / 2);
            weaponSprites.push_back(sprite);
        }

        sf::Text label;
        label.setFont(font);
        label.setString(weapons[i]->getWeaponName());
        label.setCharacterSize(20);
    	label.setLetterSpacing(1.7f);
        label.setFillColor(sf::Color(50, 40, 38));

        float textX = x + (boxSize - label.getLocalBounds().width) / 2;
        float textY = y + boxSize + 5;
        label.setPosition(textX, textY);
        weaponLabels.push_back(label);
    }
}

void InventoryMenu::clearContainers() {
	weaponSlots.clear();
	weaponSprites.clear();
	weaponLabels.clear();
	textures.clear();
}

void InventoryMenu::drawInventory(sf::RenderWindow& window) const {
    window.draw(background);

    for(const auto& slot : weaponSlots)
        window.draw(slot);

    for(const auto& sprite : weaponSprites)
        window.draw(sprite);

    for(const auto& label : weaponLabels)
        window.draw(label);
}

void InventoryMenu::setPosition(float x, float y) {
	background.setPosition(x, y);
	clearContainers();
	createWeaponSlots();
}

int InventoryMenu::handleClick(const sf::Vector2f& mousePosition) const {
	for (size_t i = 0; i < weaponSlots.size(); ++i) {
		if (weaponSlots[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)))
			return static_cast<int>(i);
	}
	return -1;
}

void InventoryMenu::centerInWindow(const sf::RenderWindow& window) {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
	sf::Vector2f backgroundSize = background.getSize();

	float x = (windowSize.x - backgroundSize.x) / 2.f;
	float y = (windowSize.y - backgroundSize.y) / 2.f;

	setPosition(x, y);
}
