#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Constants.h"
#include "Game.h"

/*
void DeinitalizeGame(Game& game)
{

}*/

int main()
{
	using namespace ApplesGame;

	Game game;

	int mode = 0;
	do {
		std::cout << "Choose a game mode:" << std::endl;
		std::cout << "1 - acceleration of the player's movement" << std::endl;
		std::cout << "2 - no acceleration" << std::endl;
	} while (std::cin >> mode && mode != 1 && mode != 2);

	if (mode == 1)
	{
		game.gameMode |= static_cast<uint32_t>(GameSettingBits::isAccelerated);
	}
	else if (mode == 2)
	{
		game.gameMode |= static_cast<uint32_t>(GameSettingBits::isNoAccelerated);
	}
	mode = 0;

	do
	{
		std::cout << "Choose a game mode:" << std::endl;
		std::cout << "1 - an infinite number of apples" << std::endl;
		std::cout << "2 - a finite number of apples" << std::endl;
	} while (std::cin >> mode && mode != 1 && mode != 2);

	if (mode == 1)
	{
		game.gameMode |= static_cast<uint32_t>(GameSettingBits::isInfinite);
		game.numApples = NUM_APPLES;
	}
	else if (mode == 2)
	{
		game.gameMode |= static_cast<uint32_t>(GameSettingBits::isFinite);
		do
		{
			std::cout << "Enter the desired number of apples(from 1 to 100): ";
		} while (std::cin >> mode && mode < MIN_APPLES && mode > MAX_APPLES);
		game.numApples = mode;
	}

	int seed = (int)time(nullptr);
	srand(seed);
	// init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// game initialization
	InitGame(game);

	// init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		// reduce framerate to not spam CPU and GPU
		sf::sleep(sf::milliseconds(16));

		// Calculate time Delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				delete[] game.apple;
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				delete[] game.apple;
				window.close();
				break;
			}
		}

		// update game state
		UpdateGame(game, deltaTime);

		// draw game
		window.clear();
		DrawGame(game, window);

		window.display();
	}

	// deinitialization
	//DeinitalizeGame(game);

	return 0;
}