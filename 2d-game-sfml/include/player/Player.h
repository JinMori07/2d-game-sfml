#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {	

public:

	Player();

	void update(float gravity);
	void handleInput(int speed_upgrade);
	void draw(sf::RenderWindow& window) const;
	sf::FloatRect getBounds() const;
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

private:
	sf::SoundBuffer buffer_jump;
	std::optional<sf::Sound> sound_jump;

	sf::RectangleShape shape;
	sf::Texture texture_player;
	float velocity;
	bool onGround;

};