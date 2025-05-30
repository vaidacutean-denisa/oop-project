#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

class AssetsManager {
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:

    // methods
    bool loadTexture(const std::string& id, const std::string& path);
    bool loadFont(const std::string& id, const std::string& path);

    // getters
    sf::Texture& getTexture(const std::string& id);
    sf::Font& getFont(const std::string& id);
    sf::Sprite getScaledSprite(const std::string &id, const sf::Vector2u &targetSize);
};

#endif //ASSETSMANAGER_H
