#include "../headers/AssetsManager.h"
#include "../headers/GameExceptions.h"

#include <iostream>

bool AssetsManager::loadTexture(const std::string &id, const std::string &path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    	throw ResourceLoadException(path);

    textures.emplace(id, std::move(texture));
    return true;
}

bool AssetsManager::loadFont(const std::string &id, const std::string &path) {
    sf::Font font;
    if (!font.loadFromFile(path))
    	throw ResourceLoadException(path);

    fonts.emplace(id, std::move(font));
    return true;
}

sf::Texture& AssetsManager::getTexture(const std::string &id) {
	try {
		return textures.at(id);
	} catch (const std::out_of_range&) {
		throw ResourceLoadException("Texture not found: " + id);
	}
}

sf::Font& AssetsManager::getFont(const std::string &id) {
	try {
		return fonts.at(id);
	} catch (const std::out_of_range&) {
		throw ResourceLoadException("Font not found: " + id);
	}
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