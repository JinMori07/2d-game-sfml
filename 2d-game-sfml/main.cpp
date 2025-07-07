#include "include/game/Game.h"
#include <SFML/Audio.hpp>
#include <iostream>
#pragma warning(disable: 4996)
#include <cstdlib>

int main() {
	sf::Music music;
	if (!music.openFromFile("assets/sounds/monster.mp3"))
	{
		throw std::runtime_error("Error loading music - monster.mp3");
	} 
	music.setLooping(true);
	music.setVolume(0);
	music.play();
	Game game;
	game.run();
	return 0;
}