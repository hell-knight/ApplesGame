#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// init player state
		player.position = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		// init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);

		// init player sound
		player.soundEat.setBuffer(game.eatenSoundBuf);
		player.soundCrash.setBuffer(game.crashSoundBuf);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		const sf::Vector2f safeScale = GetScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE);

		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			player.sprite.setScale(safeScale.x, safeScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Up:
		{
			player.sprite.setScale(safeScale.x, safeScale.y);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(safeScale.x, safeScale.y);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-safeScale.x, safeScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(player.sprite);
	}

	void UpdatePlayerState(Player& player, float deltaTime)
	{
		// Update player state
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			player.position.x += player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			player.position.y -= player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.speed * deltaTime;
			break;
		}
		}
	}

	/*void CheckBorderCollision(Game& game)
	{
		// Check screen border collision
		if (game.player.position.x - PLAYER_SIZE / 2.f < 0 || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			game.player.position.y - PLAYER_SIZE / 2.f < 0 || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			game.blsPause = true;
			game.PauseTimeLeft = PAUSE_LENGHT;

			// Crash sound player
			game.player.soundCrash.play();
		}
	}*/
}
