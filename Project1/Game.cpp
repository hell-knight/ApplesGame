#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	void RestartGame(Game& game)
	{
		// init player state
		InitPlayer(game.player, game);

		// init apples
		game.apple = new Apple[game.numApples];
		for (int i = 0; i < game.numApples; ++i)
		{
			InitApples(game.apple[i], game);
		}

		// init stones
		for (int i = 0; i < NUM_STONES; ++i)
		{
			InitStones(game.stone[i], game);
		}

		// init game global state
		game.numEatenApples = 0;
		game.blsPause = false;
		game.PauseTimeLeft = 0.f;
	}

	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.crashSoundBuf.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.eatenSoundBuf.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Black.ttf"));

		InitUI(game.uiState, game);
		RestartGame(game);
	}

	void HandleInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
		}
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (!game.blsPause)
		{
			HandleInput(game);

			UpdatePlayerState(game.player, deltaTime);

			// Check screen border collision
			if (game.player.position.x - PLAYER_SIZE / 2.f < 0 || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				game.player.position.y - PLAYER_SIZE / 2.f < 0 || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				StartGameoverState(game);
			}

			// Check stones collision
			for (int i = 0; i < NUM_STONES; ++i)
			{
				if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
					game.stone[i].position, { STONES_SIZE, STONES_SIZE }))
				{
					StartGameoverState(game);
				}
			}

			// check apple collision
			for (int i = 0; i < game.numApples; ++i)
			{
				if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
					game.apple[i].position, APPLE_SIZE / 2.f) && !game.apple[i].isAppleEatan)
				{
					//sound eat apple
					game.player.soundEat.play();

					game.numEatenApples++;
					game.totalEatenApples++;
					// Update player speed
					if (game.gameMode & static_cast<uint32_t>(GameSettingBits::isAccelerated))
					{
						game.player.speed += ACCELERATION;
					}
					// Creating a New Apple
					if (game.gameMode & static_cast<uint32_t>(GameSettingBits::isInfinite))
					{
						game.apple[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					else
					{
						game.apple[i].isAppleEatan = true;
					}
				}
			}
		}
		else
		{
			if (game.PauseTimeLeft <= 0)
			{
				InitLeaderboard(game);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					RestartGame(game);
				}
			}
			else
			{
				game.PauseTimeLeft -= deltaTime;
			}
		}
		UpdateUI(game.uiState, game);
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.blsPause && game.PauseTimeLeft <= 0)
		{
			DrawLeaderboard(game, window);
		}
		else
		{
			DrawPlayer(game.player, window);
			for (int i = 0; i < game.numApples; ++i)
			{
				if (!game.apple[i].isAppleEatan)
				{
					DrawApple(game.apple[i], window);
				}
			}
			for (int i = 0; i < NUM_STONES; ++i)
			{
				DrawStone(game.stone[i], window);
			}
			DrawUI(game.uiState, window);
		}
	}

	void StartGameoverState(Game& game)
	{
		game.blsPause = true;
		game.PauseTimeLeft = PAUSE_LENGHT;

		game.player.soundCrash.play();
		game.uiState.isGameOverText = game.blsPause;
		game.uiState.gameOverScoreText.setString("Your scores: " + std::to_string(game.numEatenApples));
	}
}