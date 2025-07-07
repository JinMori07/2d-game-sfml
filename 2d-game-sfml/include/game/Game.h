#pragma once
#include <SFML/Graphics.hpp>
#include "../player/Player.h"
#include "../watermelon/Watermelon.h"
#include "../button/button.h"
#include "../gameState/gameState.h"
#include <optional>
#include <SFML/Audio.hpp>
#include <filesystem>

class Game {

public:

	bool shop_open = false;
	Game();
	void run();

private:

	void handleEvents();
	void update();
	void render();
	void reset();

	// sounds
	sf::SoundBuffer  buffer_jump;
	sf::SoundBuffer buffer_collecting;
	std::optional<sf::Sound> sound;

	// gamestate
	GameState currentState = GameState::Start_menu;

	// font
	sf::Font font;

	// text
	std::optional<sf::Text> scoreText;
	std::optional<sf::Text> money_text;
	std::optional<sf::Text> title;

	// score
	int watermelon_score = 0;
	float money = 0;
	int speed_upgrades = 0;

	// window
	sf::RenderWindow window;

	// objects
	Player player;
	Watermelon watermelon;
	sf::RectangleShape shop_rectangle;

	// buttons
	std::optional<Button> play; // play button
	std::optional<Button> cstm; // convert score to money
	std::optional<Button> shop_button; // shop button
	std::optional<Button> shop_upgrade_speed; // speed upgrade button
	std::optional<Button> load_from_save; //load from save file button
	std::optional<Button> save_game_quit; // save the game and quit button

	// background
	sf::RectangleShape sky;
	sf::RectangleShape grass;

	// textures backgound
	sf::Texture texture_sky;
	sf::Texture texture_grass;

	// clock watermelon
	sf::Clock clock_watermelon;
	float delay = 0.1f;
	bool respawn = true;
	
	// save file path
	std::filesystem::path target;
	std::filesystem::path file_name_save = "12512sadag.txt";
	std::filesystem::path full_path;
};