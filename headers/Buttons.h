#ifndef BUTTONS_H
#define BUTTONS_H

#include <SFML/Graphics.hpp>

template <typename T>
class Buttons {
    sf::RectangleShape button;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoveredColor;
    sf::Color clickedColor;
    sf::Color outlineColor;

	T labelData;
public:
    // constructor
    Buttons(sf::Vector2f size, sf::Vector2f position, const std::string& label, const sf::Font& font,
                const sf::Color& idleColor_, const sf::Color& hoveredColor_, const sf::Color& clickedColor_,
                const sf::Color& outlineColor_, float outlineThickness_, const T& val);

    // methods
    void updateButtonColor(const sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePosition) const;
    void drawButton(sf::RenderWindow& window) const;

    // getter
    std::string getLabel() const;
	T getLabelData() const { return labelData; }
	void setLabelData(const T& data) { labelData = data; }
	const sf::RectangleShape& getButtonShape() const { return button; }

	T getValue() const;
};

template <typename T>
const Buttons<T>* getClickedButton(const std::vector<Buttons<T>>& buttons, const sf::Vector2f& mousePos) {
	for (const auto& button : buttons) {
		if (button.getButtonShape().getGlobalBounds().contains(mousePos)) {
			return &button;
		}
	}
	return nullptr;
}

#include "../templates/Buttons.tpp"

#endif //BUTTONS_H
