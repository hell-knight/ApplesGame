#include "Stone.h"
#include "Game.h"

namespace ApplesGame
{
	void InitStones(Stone& stone, const Game& game)
	{
		// init stones
		stone.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		// init stone sprite
		stone.sprite.setTexture(game.stoneTexture);
		SetSpriteSize(stone.sprite, STONES_SIZE, STONES_SIZE);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
	}

	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.position.x, stone.position.y);
		window.draw(stone.sprite);
	}
}