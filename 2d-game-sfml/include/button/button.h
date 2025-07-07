#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
	Button(const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Font& font,
		const std::string& label,
		const int& charachter_size,
		const bool& center);

	// click/hover logic
	bool update(const sf::RenderWindow& window);

	// draw on screen
	void draw(sf::RenderWindow& window) const;

	// color setters
	void setNormalColor(const sf::Color& color);
	void setHoverColor(const sf::Color& color);
	void setPressedColor(const sf::Color& color);
	void setOutlineThicknessAndColor(int thickness, const sf::Color& color);
	void setLabel(std::string newLabel);

private:
	// shape and label
	sf::RectangleShape button;
	sf::Text text;
	sf::CircleShape cross;

	bool wasPressedInside = false;

	// colors
	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
};