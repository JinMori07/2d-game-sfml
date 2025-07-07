#include "Watermelon.h"
#include <cstdlib>

Watermelon::Watermelon()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	watermelon.setSize({ 100.f, 50.f });
	watermelon.setOrigin({ 50.f, 25.f });
	
	if (!texture_watermelon.loadFromFile("assets/images/watermelon.png"))
	{
		throw std::runtime_error("Error from load texture - watermelon");
	}
	watermelon.setTexture(&texture_watermelon);

	float pos_1 = (std::rand() % (1024 + 1));
	float pos_2 = (std::rand() % (430 + 1));
	watermelon.setPosition({ pos_1, pos_2 });
}

void Watermelon::respawn()
{
	float pos_1 = (std::rand() % (1024 + 1));
	float pos_2 = (std::rand() % (430 + 1));
	watermelon.setPosition({ pos_1, pos_2 });
}

sf::FloatRect Watermelon::getBounds() const
{
	return watermelon.getGlobalBounds();
}

void Watermelon::draw(sf::RenderWindow& window) const
{
	window.draw(watermelon);
}