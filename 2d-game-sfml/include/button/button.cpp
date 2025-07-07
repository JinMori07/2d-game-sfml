#include "button.h"
#include <iostream>
#include <string>

Button::Button(const sf::Vector2f& size,
	const sf::Vector2f& position,
	const sf::Font& font,
	const std::string& label,
	const int& charachter_size,
	const bool& center )
	: text(font)
{
	normalColor = sf::Color::White;
	hoverColor = sf::Color(211, 211, 211);
	pressedColor = sf::Color(201, 255, 246);

	if (center)
	{
		button.setSize(size);
		button.setPosition(position);
		button.setOrigin(button.getSize() / 2.f);
		button.setFillColor(normalColor);
		
		text.setFont(font);
		text.setString(label);
		text.setCharacterSize(charachter_size);
		text.setFillColor(sf::Color::White);
		text.setOutlineThickness(2);

		// Get bounds of the button
		auto tb = text.getLocalBounds();

		text.setOrigin
		({
			std::round(tb.position.x + tb.size.x / 2.f),
			std::round(tb.position.y + tb.size.y / 2.f)
		});


		text.setPosition(button.getPosition());
	}
	else
	{
		button.setSize(size);
		button.setPosition(position);
		button.setFillColor(normalColor);

		text.setFont(font);
		text.setString(label);
		text.setCharacterSize(charachter_size);
		text.setFillColor(sf::Color::White);
		text.setOutlineThickness(2);



		// Get bounds of the button
		auto tb = text.getLocalBounds();

		text.setOrigin
		({
			std::round(tb.position.x + tb.size.x / 2.f),
			std::round(tb.position.y + tb.size.y / 2.f)
			});

		sf::Vector2f buttonCenter = button.getPosition() + button.getSize() / 2.f;

		text.setPosition(buttonCenter);
	}
}


void Button::setOutlineThicknessAndColor(int thickness, const sf::Color& color)
{
	button.setOutlineThickness(thickness);
	button.setOutlineColor(color);
}

void Button::setNormalColor(const sf::Color& color) 
{
	normalColor = color;
}

void Button::setHoverColor(const sf::Color& color) 
{
	hoverColor = color;
}

void Button::setLabel(std::string newLabel)
{
	text.setString(newLabel);
}

void Button::setPressedColor(const sf::Color& color)
{
	pressedColor = color;	
}

bool Button::update(const sf::RenderWindow& window)
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF = static_cast<sf::Vector2f>(mousePixel);
	bool contains = button.getGlobalBounds().contains(mousePosF);
	bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);


	if (contains && mouseDown)
	{	
		wasPressedInside = true;
		button.setFillColor(pressedColor);
		return false;
	}
	if (!mouseDown && wasPressedInside)
	{
		wasPressedInside = false;
		button.setFillColor(contains ? hoverColor : normalColor);
		if (contains)
		{
			return true;
		}
	}
	button.setFillColor(contains ? hoverColor : normalColor);
	return false;
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(button);
	window.draw(text);
	window.draw(cross);
}