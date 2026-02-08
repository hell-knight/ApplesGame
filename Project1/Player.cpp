#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);

		// init player sound
		player.soundEat.setBuffer(game.eatenSoundBuf);
		player.soundCrash.setBuffer(game.crashSoundBuf);
	}

	void SetPlayerDirection(Player& player, PlayerDirection direction)
	{
		player.direction = direction;
	}

	void SetPlayerPosition(Player& player, const Position2D& position)
	{
		player.position = position;
	}

	void SetPlayerSpeed(Player& player, float speed)
	{
		player.speed = speed;
	}

	float GetPlayerSpeed(const Player& player)
	{
		return player.speed;
	}

	Rectangle GetPlayerCollider(const Player& player)
	{
		return {player.position, PLAYER_SIZE / 2.f};
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
}
