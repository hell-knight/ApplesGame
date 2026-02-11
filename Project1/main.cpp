#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Constants.h"
#include "Game.h"

enum class GameSettingBits
{
	isInfinite = 1 << 0,
	isAccelerated = 1 << 1,
	isHardcore = 1 << 2,
	isZenMode = 1 << 3
};

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
		std::cout << "1 - with an infinite number of apples, but without the changed speed" << std::endl;
		std::cout << "2 - with 20 apples and altered speed" << std::endl;
		std::cout << "3 - with 50 apples at altered speed" << std::endl;
		std::cout << "4 - with 20 apples, but without the changed speed" << std::endl;
	} while (std::cin >> mode && mode != 1 && mode != 3 && mode != 2 && mode != 4);

	switch (mode)
	{
	case 1: game.gameMode |= static_cast<uint32_t>(GameSettingBits::isInfinite); break;
	case 2: game.gameMode |= static_cast<uint32_t>(GameSettingBits::isAccelerated); break;
	case 3: game.gameMode |= static_cast<uint32_t>(GameSettingBits::isHardcore); break;
	case 4: game.gameMode |= static_cast<uint32_t>(GameSettingBits::isZenMode); break;
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
