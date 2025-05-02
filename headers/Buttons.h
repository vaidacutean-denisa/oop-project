#ifndef BUTTONS_H
#define BUTTONS_H

#include <SFML/Graphics.hpp>

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
    std::string getLabel() const;
};

#endif //BUTTONS_H
