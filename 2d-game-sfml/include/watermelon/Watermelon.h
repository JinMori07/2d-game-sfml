#pragma once
#include <SFML/Graphics.hpp>

class Watermelon {
public:
	Watermelon();
	void respawn();
	void draw(sf::RenderWindow& window) const;
	sf::FloatRect getBounds() const;
private:
	sf::RectangleShape watermelon;
	sf::Texture texture_watermelon;
};