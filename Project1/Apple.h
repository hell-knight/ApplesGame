#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Apple
	{
		Position2D position;
		sf::Sprite sprite;
		bool isAppleEatan = false;
	};

	struct Game;

	void InitApples(Apple& apple, const Game& game);

	void DrawApple(Apple& apple, sf::RenderWindow& window);
}