#ifndef BUTTONS_TPP
#define BUTTONS_TPP

#include "../headers/Buttons.h"

template <typename T>
Buttons<T>::Buttons(const sf::Vector2f size, const sf::Vector2f position, const std::string& label, const sf::Font& font,
                    const sf::Color& idleColor_, const sf::Color& hoveredColor_, const sf::Color& clickedColor_,
                    const sf::Color& outlineColor_, float outlineThickness_, const T& value)
        : idleColor(idleColor_), hoveredColor(hoveredColor_), clickedColor(clickedColor_), outlineColor(outlineColor_), labelData(value)
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

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(position + size / 2.0f);
}

template <typename T>
void Buttons<T>::updateButtonColor(const sf::RenderWindow &window) {
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

    if (button.getGlobalBounds().contains(mousePosition)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            button.setFillColor(clickedColor);
        else
            button.setFillColor(hoveredColor);
    } else
        button.setFillColor(idleColor);
}

template <typename T>
bool Buttons<T>::isClicked(sf::Vector2f mousePosition) const {
    return button.getGlobalBounds().contains(mousePosition) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

template <typename T>
void Buttons<T>::drawButton(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(text);
}

template <typename T>
std::string Buttons<T>::getLabel() const {
    return text.getString();
}

template <typename T>
T Buttons<T>::getValue() const {
    return labelData;
}

#endif // BUTTONS_TPP
