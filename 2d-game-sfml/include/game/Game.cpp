#include "Game.h"
#include <iostream>
#include <cmath>
#include <format>	
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <vector>
#pragma warning(disable: 4996)

Game::Game()
	// window
	: window(sf::VideoMode({ 1024, 712 }), "2d-game-sfml")
{

	const char* appdata = std::getenv("APPDATA");
	if (!appdata)
	{
		throw std::runtime_error("Error finding appdata variable");
	}
	
	target = std::filesystem::path(appdata) / "as0d87f0ahs1254091" / "as0d87f0ah21254091";

	if (std::filesystem::create_directories(target))
	{
		std::cout << "Created: " << target << std::endl;
	}
	else
	{
		std::cout << target << " already exists\n";
	}

	full_path = target / file_name_save;

	// font check
	if (!font.openFromFile("assets/fonts/AlteHaasGroteskRegular.ttf"))
	{
		throw std::runtime_error("Error loading font");
	}

	// sky image
	sky.setSize({ 1024.f, 712.f });
	sky.setOrigin({ 512.f, 356.f });
	sky.setPosition({ 512.f, 356.f });
	if (!texture_sky.loadFromFile("assets/images/sky.jpg"))
	{
		throw std::runtime_error("Error loading image - sky.jpg");
	}
	sky.setTexture(&texture_sky);

	// Title
	title.emplace(font);
	title->setOutlineThickness(1);
	title->setCharacterSize(50);
	title->setPosition({ 365, 200 });
	title->setString("2d-game-sfml");
	title->setOutlineThickness(4);
	title->setOutlineColor(sf::Color::Black);

	// play button
	play.emplace
	(
		sf::Vector2f{ 200, 100 }, // size
		sf::Vector2f{ 1024 / 2 , 712 / 2 }, // position
		font,
		"New game",
		24,
		true
	);
	int thickness_play = 3;

	play->setNormalColor(sf::Color::Color(255, 17, 0, 100));
	play->setHoverColor(sf::Color::Color(255, 17, 0, 150));
	play->setPressedColor(sf::Color::Color(255, 17, 0, 200));
	play->setOutlineThicknessAndColor(thickness_play, (sf::Color::Black));

	// load from save button
	load_from_save.emplace
	(
		sf::Vector2f{ 200, 50 },
		sf::Vector2f{ 1024 / 2, 712 / 2 + 90 },
		font,
		"Load save",
		24,
		true
	);
	play->setOutlineThicknessAndColor(thickness_play, (sf::Color::Black));



	// scoreText
	scoreText.emplace(font);
	scoreText->setCharacterSize(24);
	scoreText->setPosition({ 12,13 });
	scoreText->setFillColor(sf::Color::White);
	scoreText->setString("Watermelons: 0");
	scoreText->setOutlineThickness(2);

	// money
	money_text.emplace(font);
	money_text->setCharacterSize(24);
	money_text->setPosition({ 12, 75 });
	money_text->setFillColor(sf::Color::White);
	money_text->setString("Money: 0");
	money_text->setOutlineThickness(2);

	// grass image
	grass.setSize({ 1024.f, 200.f });
	grass.setPosition({ 0.f, 512.f });
	if (!texture_grass.loadFromFile("assets/images/grass.png"))
	{
		throw std::runtime_error("Error loading image - grass.png");
	}
	grass.setTexture(&texture_grass);

	// shop button
	shop_button.emplace(
		sf::Vector2f{ 100, 75 },
		sf::Vector2f{ 912, 12 },
		font,
		"shop",
		24,
		false
	);
	int thickness_shop = 3;
	shop_button->setOutlineThicknessAndColor(thickness_shop, (sf::Color::Black));

	//  save & quit button
	save_game_quit.emplace
	(
		sf::Vector2f{ 120, 75 },
		sf::Vector2f{ 912 - 140, 12 },
		font,
		"Quit & Save",
		18,
		false
	);
	save_game_quit->setOutlineThicknessAndColor(thickness_shop, (sf::Color::Black));
	
	// convert score to money
	cstm.emplace
	(
		sf::Vector2f{ 220, 50 },
		sf::Vector2f{ 240, 4 },
		font,
		"convert watermelon to money",
		15,
		false
	);
	cstm->setOutlineThicknessAndColor(2, sf::Color::Black);

	//shop rectangle
	shop_rectangle.setSize({ 600, 400 });
	shop_rectangle.setOrigin(shop_rectangle.getSize() * 0.5f);
	shop_rectangle.setPosition(static_cast<sf::Vector2f>(window.getSize()) * 0.5f);
	shop_rectangle.setFillColor(sf::Color(0, 0, 0, 155));
	shop_rectangle.setOutlineThickness(3);

	// shop upgrade speed
	shop_upgrade_speed.emplace
	(
		sf::Vector2f{ 150, 90 },
		shop_rectangle.getPosition() + sf::Vector2f{-220.f, -150.f},
		font,
		"Speed 0, cost = 0",
		15,
		true
	);
	shop_upgrade_speed->setOutlineThicknessAndColor(1, sf::Color::Color::Yellow);

	// sound
	if (!buffer_jump.loadFromFile("assets/sounds/jump.mp3"))
	{
		throw std::runtime_error("Error loading sound - jump.mp3");
	}

	if (!buffer_collecting.loadFromFile("assets/sounds/collect.mp3"))
	{
		throw std::runtime_error("Error loading sound - collect.mp3");
	}
	sound.emplace
	(
		buffer_jump
	);

}

void Game::handleEvents()
{
	// pollevent
	while (std::optional event = window.pollEvent()) {

		if (event->is<sf::Event::Closed>()) {
			window.close();
		}

		if (load_from_save->update(window))
		{
			if (std::filesystem::exists(full_path))
			{
				std::cout << "loading from save\n";
				std::ifstream saveFile;

				std::vector<std::string> tokens;
				std::string token;

				saveFile.open(full_path);
				while (saveFile >> token)
				{
					tokens.push_back(token);
				}
				saveFile.close();
				watermelon_score += std::stoi(tokens[0]);
				money += std::stof(tokens[1]);
				speed_upgrades += std::stoi(tokens[2]);
				currentState = GameState::Playing;

			}
			else
			{
				std::cout << "No save file starting new game";
				currentState = GameState::Playing;
			}
		}

		if (save_game_quit->update(window))
		{
			if (std::filesystem::exists(full_path))
			{
				std::cout << "File exists \n";
				std::ofstream saveFile;
				saveFile.open(full_path);
				saveFile << watermelon_score << "\n";
				saveFile << money << "\n";
				saveFile << speed_upgrades;
				saveFile.close();
			}
			else
			{
				std::cout << "Doesnt exist \n" << "making the file; ";
				std::ofstream saveFile;
				saveFile.open(full_path);
				saveFile << watermelon_score << "\n";
				saveFile << money << "\n";
				saveFile << speed_upgrades;
				saveFile.close();
			}
			window.close();
		}

		bool shopClicked = shop_button->update(window);

		if (shopClicked)
		{
			shop_open = !shop_open;
			currentState = shop_open ? GameState::shop_1 : GameState::Playing;
		}
		else if (play->update(window))
		{
			currentState = GameState::Playing;
		}


		if (play->update(window))
		{
			currentState = GameState::Playing;
		}

		int speed_price = static_cast<int>(round(speed_upgrades + 1) * pow(2, speed_upgrades + 1));

		if (shop_upgrade_speed->update(window) && (money >= speed_price))
		{
			speed_upgrades += 1;
			money -= speed_price;
			currentState = GameState::shop_1;
		}

		std::string newLabel = "Speed " + std::to_string(speed_upgrades) + ", Cost " + std::to_string(static_cast<int>(round(speed_price)));
		shop_upgrade_speed->setLabel(newLabel);

		if (cstm->update(window) && watermelon_score > 0)
		{
			money += (watermelon_score * 0.25f);
			watermelon_score = 0;
		}
	}	

	// player input
	player.handleInput(speed_upgrades);
}

void Game::update()
{

	// gravity player
	const float gravity = 1.0f;
	player.update(gravity);

	//  collision player nd watermelon
	if (player.getBounds().findIntersection(watermelon.getBounds())) 
	{
		watermelon.respawn();
		watermelon_score++;
		sound->setBuffer(buffer_collecting);
		sound->play();

	}
	scoreText->setString("Watermelon: " + std::to_string(watermelon_score));
	money_text->setString("Money: " + std::to_string(money));
}

void Game::render()
{
	// window
	window.clear();
	window.setFramerateLimit(60);

	window.draw(sky);

	switch (currentState)
	{
	case GameState::Start_menu:

		//button
		play->draw(window);
		load_from_save->draw(window);
		window.draw(*title);
		break;

	case GameState::Playing:

		// background 
		window.draw(grass);

		// player
		player.draw(window);

		// collectibles
		watermelon.draw(window);

		// hud
		window.draw(*scoreText);
		window.draw(*money_text);
		shop_button->draw(window);
		save_game_quit->draw(window);
		cstm->draw(window);

		break;

	case GameState::shop_1:

		// background 
		window.draw(grass);

		// player
		player.draw(window);

		// collectibles
		watermelon.draw(window);

		// hud
		window.draw(shop_rectangle);
		window.draw(*scoreText);
		window.draw(*money_text);
		shop_button->draw(window); // buttton
		window.draw(shop_rectangle); // rectangle
		shop_upgrade_speed->draw(window); // button
		cstm->draw(window);
		break;
	}

	// render
	window.display();
}

void Game::run()
{
	// game run
	while (window.isOpen()) {
		handleEvents();
		update();
		render();
	}
}