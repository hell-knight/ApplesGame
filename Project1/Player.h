#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D position;
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sprite sprite;
		sf::Sound soundEat;
		sf::Sound soundCrash;
	};

	struct Game;

	void InitPlayer(Player& player, const Game& game);

	void SetPlayerDirection(Player& player, PlayerDirection direction);
	void SetPlayerPosition(Player& player, const Position2D& position);
	void SetPlayerSpeed(Player& player, float speed);
	float GetPlayerSpeed(const Player& player);

	Rectangle GetPlayerCollider(const Player& player);

	void DrawPlayer(Player& player, sf::RenderWindow& window);

	void UpdatePlayerState(Player& player, float deltaTime);

	void CheckBorderCollision(Game& game);
}
