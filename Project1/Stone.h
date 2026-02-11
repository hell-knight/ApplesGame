#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Stone
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitStones(Stone& stone, const Game& game);

	void DrawStone(Stone& stone, sf::RenderWindow& window);
}