#include "Leaderboard.h"
#include "Game.h"
//#include <iostream>

namespace ApplesGame
{
	void InitLeaderboard(Game& game)
	{
		/*
		// search and replace points for a player
		auto it = std::find_if(game.leaderboard.recordList.begin(),
			game.leaderboard.recordList.end(), [](const Record& r) {return r.name == "Player"; });
		if (it != game.leaderboard.recordList.end())
		{
			it->score = game.totalEatenApples;
		}
		else
		{
			game.leaderboard.recordList.push_back({ "Player", game.numEatenApples });
		}
		*/

		// search and replace points for a player
		auto it = game.leaderboard.list.find("Player");
		if (it != game.leaderboard.list.end())
		{
			it->second = game.totalEatenApples;
		}
		else
		{
			game.leaderboard.list["Player"] = game.numEatenApples;
		}

		// Preparing a sorted list for output
		std::vector<Record> recordList;
		recordList.reserve(game.leaderboard.list.size());
		for (const auto& column : game.leaderboard.list)
		{
			recordList.push_back({column.first, column.second});
		}

		// table sorting
		MyInsertionSort(recordList);

		// Output of records
		for (size_t i = 0; i < recordList.size(); ++i)
		{
			float columnHeight = 100.f + i * 25.f;
			// place
			game.uiState.placeLeaderboardText[i].setString(std::to_string(i + 1) + ".");
			game.uiState.placeLeaderboardText[i].setPosition(150.f, columnHeight);

			// name
			game.uiState.nameLeaderboardText[i].setString(recordList[i].name);
			game.uiState.nameLeaderboardText[i].setPosition(220.f, columnHeight);

			// score
			game.uiState.scoreLeaderboardText[i].setString(std::to_string(recordList[i].score));
			game.uiState.scoreLeaderboardText[i].setPosition(600.f, columnHeight);
		}
	}

	void MyInsertionSort(std::vector<Record>& list)
	{
		// table sorting
		size_t sizeTable = list.size();
		//std::cout << sizeTable << std::endl;
		// Go through all the elements, starting with the second one
		for (size_t i = 1; i < sizeTable; ++i)
		{
			Record key = list[i];	// the current element that we will insert
			size_t last = i;			// index of the last element of the sorted part

			while (last > 0 && list[last - 1].score < key.score)
			{
				list[last] = list[last - 1];
				last--;
			}

			// Insert the key into the vacant space
			list[last] = key;
		}
	}
	
	void DrawLeaderboard(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.uiState.inputHitLeaderboardText);
		window.draw(game.uiState.headLeaderboardText);
		for (size_t i = 0; i < game.leaderboard.list.size(); ++i)
		{
			window.draw(game.uiState.placeLeaderboardText[i]);
			window.draw(game.uiState.nameLeaderboardText[i]);
			window.draw(game.uiState.scoreLeaderboardText[i]);
		}
		window.draw(game.uiState.bottomLeaderboardText);
	}
}