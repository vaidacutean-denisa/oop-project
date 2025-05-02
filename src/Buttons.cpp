#include "Buttons.h"


std::string Buttons::getLabel() const { return text.getString(); }

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
