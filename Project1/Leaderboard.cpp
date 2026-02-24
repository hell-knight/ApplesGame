#include "Leaderboard.h"
#include "Game.h"
#include <iostream>

namespace ApplesGame
{
	void InitLeaderboard(std::map<std::string, int>& list)
	{
		UpdateScore(list, "Alice", 100);
		UpdateScore(list, "Bob", 80);
		UpdateScore(list, "Carol", 64);
		UpdateScore(list, "Dave", 55);
		UpdateScore(list, "Egor", 41);
		UpdateScore(list, "Filip", 35);
		UpdateScore(list, "George", 23);
		UpdateScore(list, "Hanna", 19);
		UpdateScore(list, "Ivan", 12);
		UpdateScore(list, "Player", 0);
	}

	void UpdateScore(std::map<std::string, int>& list, const std::string& name, int score)
	{
		if (!VerifNameScore(name, score))
		{
			return;
		}

		auto it = list.find(name);
		if (it != list.end())
		{
			if (score > it->second)
			{
				it->second = score;
			}
		}
		else
		{
			list[name] = score;
		}
	}

	bool VerifNameScore(const std::string& name, int score)
	{
		if (name.empty() || name.find_first_not_of(" \t") == std::string::npos)
		{
			std::cerr << "Error: Player name cannot be empty or consist only of spaces\n";
			return false;
		}

		if (score < 0)
		{
			std::cerr << "Error: points cannot be negative ( " << score << " )\n";
			return false;
		}
		return true;
	}

	std::vector<Record> BuildSortedRecords(std::map<std::string, int>& list)
	{
		std::vector<Record> result;
		result.reserve(list.size());

		for (const auto& [name, score] : list)
		{
			result.push_back({name, score});
		}

		MyInsertionSort(result);

		return result;
	}
	
	void DrawLeaderboard(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.uiState.inputHitLeaderboardText);
		window.draw(game.uiState.headLeaderboardText);

		std::vector<Record> sortedList = BuildSortedRecords(game.leaderboard);

		// Output of records
		for (size_t i = 0; i < sortedList.size(); ++i)
		{
			float columnHeight = 100.f + i * 25.f;

			sf::Text place(std::to_string(i + 1) + ".", game.font, 20);
			sf::Text name(sortedList[i].name, game.font, 20);
			sf::Text score(std::to_string(sortedList[i].score), game.font, 20);

			place.setPosition(150.f, columnHeight);
			name.setPosition(220.f, columnHeight);
			score.setPosition(600.f, columnHeight);

			if (sortedList[i].name == PLAYER_NAME)
			{
				place.setFillColor(sf::Color::Yellow);
				name.setFillColor(sf::Color::Yellow);
				score.setFillColor(sf::Color::Yellow);
			}

			window.draw(place);
			window.draw(name);
			window.draw(score);
		}
		window.draw(game.uiState.bottomLeaderboardText);
	}
}