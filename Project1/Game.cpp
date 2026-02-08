#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	void InitGame(Game& game)
	{
		// load resources
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.crashSoundBuf.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.eatenSoundBuf.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Black.ttf"));

		// init game objects
		game.screenRect = {0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT};

		InitPlayer(game.player, game);

		// init apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			InitApples(game.apple[i], game);
		}

		// init stones
		for (int i = 0; i < NUM_STONES; ++i)
		{
			InitStones(game.stone[i], game);
		}

		// init background
		game.background.setSize(sf::Vector2f(game.screenRect.size.x, game.screenRect.size.y));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		// init sounds
		//game.player.soundEat.setBuffer(game.eatenSoundBuf);
		//game.player.soundCrash.setBuffer(game.crashSoundBuf);

		// init text
		InitUI(game.uiState, game);

		StartPlayingState(game);
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		// update gamestate
		if (!game.blsPause)
		{
			UpdatePlayingState(game, deltaTime);
		}
		else
		{
			UpdateGameoverState(game, deltaTime);
		}
	}

	void HandleInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			SetPlayerDirection(game.player, PlayerDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			SetPlayerDirection(game.player, PlayerDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			SetPlayerDirection(game.player, PlayerDirection::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			SetPlayerDirection(game.player, PlayerDirection::Down);
		}
	}

	void StartPlayingState(Game& game)
	{
		// init player
		SetPlayerPosition(game.player, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});
		SetPlayerSpeed(game.player, INITIAL_SPEED);
		SetPlayerDirection(game.player, PlayerDirection::Right);

		// init apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			SetApplePosition(game.apple[i], GetRandomPositionInScreen(game.screenRect));
		}

		// init stones
		for (int i = 0; i < NUM_STONES; ++i)
		{
			SetStonePosition(game.stone[i], GetRandomPositionInScreen(game.screenRect));
		}

		game.numEatenApples = 0;
		game.blsPause = false;
		game.PauseTimeLeft = 0.f;
		UpdateUI(game.uiState, game);
	}

	void StartGameoverState(Game& game)
	{
		game.blsPause = true;
		game.PauseTimeLeft = 0.f;

		// Crash sound player
		game.player.soundCrash.play();

		game.uiState.isGameOverText = game.blsPause;
		game.uiState.gameOverScoreText.setString("Your scores: " + std::to_string(game.numEatenApples));
	}

	void UpdateGameoverState(Game& game, float deltaTime)
	{
		if (game.PauseTimeLeft <= PAUSE_LENGHT)
		{
			game.PauseTimeLeft += deltaTime;
			game.background.setFillColor(sf::Color::Red);
		}
		else
		{
			// reset background
			game.background.setFillColor(sf::Color::Black);

			StartPlayingState(game);
		}
	}

	void DeinitalizeGame(Game& game)
	{
	}

	void UpdatePlayingState(Game& game, float deltaTime)
	{
		
		HandleInput(game);

		UpdatePlayerState(game.player, deltaTime);
			
			
		// check screen border collision
		if (!DoShapesCollide(GetPlayerCollider(game.player), game.screenRect))
		{
			StartGameoverState(game);
		}
			
		// find player collisions with stones
		for (int i = 0; i < NUM_STONES; ++i)
		{
			if (DoShapesCollide(GetPlayerCollider(game.player), GetStoneCollider(game.stone[i])))
			{
				StartGameoverState(game);
			}
		}

		// find player collisions with apples
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (DoShapesCollide(GetPlayerCollider(game.player), GetAppleCollider(game.apple[i])))
			{
				//sound eat apple
				game.player.soundEat.play();

				++game.numEatenApples;
				// Update player speed
				SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
				// Creating a New Apple
				SetApplePosition(game.apple[i], GetRandomPositionInScreen(game.screenRect));
				UpdateUI(game.uiState, game);
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		DrawPlayer(game.player, window);
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			DrawApple(game.apple[i], window);
		}
		for (int i = 0; i < NUM_STONES; ++i)
		{
			DrawStone(game.stone[i], window);
		}

		// draw text
		DrawUI(game.uiState, window);
	}
}