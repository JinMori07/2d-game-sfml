#include "Player.h"
#include <SFML/Audio.hpp>

Player::Player()
	: velocity(0.f), onGround(true)
{
	shape.setSize({ 150.f, 150.f });
	shape.setOrigin({ 75.f, 75.f });

	if (!texture_player.loadFromFile("assets/images/charachter.png")) 
    {
		throw std::runtime_error("Failed to load texture - player");
	}
	shape.setTexture(&texture_player);

	shape.setPosition({ 512.f, 300.f });

    if (!buffer_jump.loadFromFile("assets/sounds/jump.mp3")) 
    {
        throw std::runtime_error("Failed to load sound - jump.mp3");
    }

    sound_jump.emplace
    (
        buffer_jump
    );

}

void Player::update(float gravity) 
{
    velocity += gravity;
    shape.move({ 0.f, velocity });
    
    if (shape.getPosition().y >= 430.f) {
        shape.setPosition({ shape.getPosition().x, 430.f });
        velocity = 0.f;
        onGround = true;
    }
}

void Player::handleInput(int speed_upgrade)
{
    float speed_multiplier = speed_upgrade * 0.5f + 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && onGround == true) {
        velocity = -30.f; // basically jump strength
        onGround = false;
        sound_jump->play();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        shape.move({ -7.5f * speed_multiplier, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        shape.move({ 7.5f * speed_multiplier, 0.f });
    }
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const
{
    return shape.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
    shape.setPosition({ x, y });
}

sf::Vector2f Player::getPosition() const
{
    return shape.getPosition();
}