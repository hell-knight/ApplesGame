#include "UI.h"
#include <string>
#include "Game.h"

namespace ApplesGame
{
	void InitUI(UIState& uiState, Game& game)
	{
		uiState.scoreText.setFont(game.font);
		uiState.scoreText.setCharacterSize(20);
		uiState.scoreText.setFillColor(sf::Color::White);
		uiState.scoreText.setPosition(10.f, 10.f);

		uiState.inputHitText.setFont(game.font);
		uiState.inputHitText.setCharacterSize(20);
		uiState.inputHitText.setFillColor(sf::Color::White);
		uiState.inputHitText.setString("Use arrow keys to move, ESC to exit");
		uiState.inputHitText.setPosition(SCREEN_WIDTH - uiState.inputHitText.getGlobalBounds().width - 20.f, 10.f);

		uiState.isGameOverText = false;
		uiState.gameOverText.setFont(game.font);
		uiState.gameOverText.setCharacterSize(100);
		uiState.gameOverText.setFillColor(sf::Color::White);
		uiState.gameOverText.setStyle(sf::Text::Bold);
		uiState.gameOverText.setString("GAME OVER");
		uiState.gameOverText.setPosition(SCREEN_WIDTH / 2.f - 200.f, SCREEN_HEIGHT / 2.f - 50.f);

		uiState.gameOverScoreText.setFont(game.font);
		uiState.gameOverScoreText.setCharacterSize(30);
		uiState.gameOverScoreText.setFillColor(sf::Color::White);
		uiState.gameOverScoreText.setString("Your score: " + std::to_string(game.numEatenApples));
		uiState.gameOverScoreText.setPosition(SCREEN_WIDTH / 2.f - uiState.inputHitText.getGlobalBounds().width / 4.f, SCREEN_HEIGHT / 2.f + 50.f);
	}

	void UpdateUI(UIState& uiState, Game& game)
	{
		uiState.scoreText.setString("Apples etan: " + std::to_string(game.numEatenApples));

		uiState.isGameOverText = game.blsPause;
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		if (uiState.isGameOverText)
		{
			window.draw(uiState.gameOverText);
			window.draw(uiState.gameOverScoreText);
		}
		else
		{
			window.draw(uiState.scoreText);
			window.draw(uiState.inputHitText);
		}
	}
}