#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "UI.h"
#include "Leaderboard.h"

namespace ApplesGame
{
	enum class GameSettingBits
	{
		isInfinite = 1 << 0,
		isAccelerated = 1 << 1,
		isNoAccelerated = 1 << 2,
		isFinite = 1 << 3
	};

	struct Game
	{
		// player data
		Player player;

		// apples data
		Apple* apple = nullptr;
		int numApples = 0;

		// stones data
		Stone stone[NUM_STONES];

		std::map<std::string, int> leaderboard;

		UIState uiState;

		// global game data
		int numEatenApples = 0;
		bool blsPause = false;
		float PauseTimeLeft = 0.f;
		uint32_t gameMode = 0;

		// recources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer crashSoundBuf;
		sf::SoundBuffer eatenSoundBuf;
		sf::Font font;
	};

	void RestartGame(Game& game);

	void InitGame(Game& game);

	void UpdateGame(Game& game, float deltaTime);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void StartGameoverState(Game& game);

	void HandleInput(Game& game);
}