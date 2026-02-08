#include "Stone.h"
#include "Game.h"

namespace ApplesGame
{
	void InitStones(Stone& stone, const Game& game)
	{
		// init stones
		//stone.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		// init stone sprite
		stone.sprite.setTexture(game.stoneTexture);
		SetSpriteSize(stone.sprite, STONES_SIZE, STONES_SIZE);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
	}

	void SetStonePosition(Stone& stone, const Position2D& position)
	{
		stone.position = position;
	}

	Rectangle GetStoneCollider(const Stone& stone)
	{
		return {stone.position, STONES_SIZE / 2.f};
	}

	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.position.x, stone.position.y);
		window.draw(stone.sprite);
	}

	void CheckStoneCollision(Game& game)
	{
		// Check stones collision
		for (int i = 0; i < NUM_STONES; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.stone[i].position, { STONES_SIZE, STONES_SIZE }))
			{
				game.blsPause = true;
				game.PauseTimeLeft = PAUSE_LENGHT;

				game.player.soundCrash.play();
			}
		}
	}
}