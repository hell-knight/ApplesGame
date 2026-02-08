#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
	void InitApples(Apple& apple, const Game& game)
	{
		// init apples
		//apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		// init apple sprite
		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void SetApplePosition(Apple& apple, const Position2D& position)
	{
		apple.position = position;
	}

	Circle GetAppleCollider(const Apple& apple)
	{
		return {apple.position, APPLE_SIZE / 2.f};
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.sprite);
	}

	/*void CheckAppleCollision(Game& game)
	{
		// check apple collision
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				game.apple[i].position, APPLE_SIZE / 2.f))
			{
				//sound eat apple
				game.player.soundEat.play();

				game.numEatenApples++;
				// Update player speed
				game.player.speed += ACCELERATION;
				// Creating a New Apple
				game.apple[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
		}
	}*/
}