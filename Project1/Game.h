#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "UI.h"

namespace ApplesGame
{
	struct Game
	{
		Rectangle screenRect;

		// player data
		Player player;

		// apples data
		Apple apple[NUM_APPLES];

		// stones data
		Stone stone[NUM_STONES];

		UIState uiState;

		// global game data
		int numEatenApples = 0;
		bool blsPause = false;
		float PauseTimeLeft = 0.f;
		sf::RectangleShape background;

		// recources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer crashSoundBuf;
		sf::SoundBuffer eatenSoundBuf;
		sf::Font font;
	};

	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinitalizeGame(Game& game);

	void HandleInput(Game& game);

	void StartPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float deltaTime);

	void StartGameoverState(Game& game);
	void UpdateGameoverState(Game& game, float deltaTime);
}