#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>


namespace ApplesGame
{
	struct UIState
	{
		bool isGameOverText = false;

		sf::Text gameOverText;
		sf::Text scoreText;
		sf::Text inputHitText;
		sf::Text gameOverScoreText;
		sf::Text inputHitLeaderboardText, headLeaderboardText, bottomLeaderboardText;
	};

	struct Game;

	void InitUI(UIState& uiState, const Game& game);

	void UpdateUI(UIState& uiState, Game& game);

	void DrawUI(UIState& uiState, sf::RenderWindow& window);
}