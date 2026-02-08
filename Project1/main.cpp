#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"


int main()
{
	using namespace ApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);
	// init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// game initialization
	Game game;
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
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
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

	DeinitalizeGame(game);

	return 0;
}
