#include "../headers/AssetsManager.h"

#include <iostream>

bool AssetsManager::loadTexture(const std::string &id, const std::string &path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cout << "Failed to load texture: " << path << '\n';
        return false;
    }
    textures.emplace(id, std::move(texture));
    return true;
}

bool AssetsManager::loadFont(const std::string &id, const std::string &path) {
    sf::Font font;
    if (!font.loadFromFile(path)) {
        std::cout << "Failed to load font: " << path << '\n';
        return false;
    }
    fonts.emplace(id, std::move(font));
    return true;
}

sf::Texture& AssetsManager::getTexture(const std::string &id) {
    return textures.at(id);
}

sf::Font& AssetsManager::getFont(const std::string &id) {
    return fonts.at(id);
}

sf::Sprite AssetsManager::getScaledSprite(const std::string& id, const sf::Vector2u& targetSize) {
    sf::Sprite sprite;
    sprite.setTexture(getTexture(id));

    const sf::Vector2u textureSize = getTexture(id).getSize();
    float scaleX = static_cast<float>(targetSize.x) / textureSize.x;
    float scaleY = static_cast<float>(targetSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    return sprite;
}