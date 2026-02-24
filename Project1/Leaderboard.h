#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


namespace ApplesGame
{
	/*
	struct Record
	{
		std::string name;
		int score;
	};

	struct Leaderboard
	{
		
		std::vector<Record> recordList = {
			{"Alice", 100},
			{"Bob", 80},
			{"Carol", 64},
			{"Dave", 55},
			{"Egor", 41},
			{"Filip", 35},
			{"George", 23},
			{"Hanna", 19},
			{"Ivan", 12}
		};
		std::map<std::string, int> list = {
			{"Alice", 100},
			{"Bob", 80},
			{"Carol", 64},
			{"Dave", 55},
			{"Egor", 41},
			{"Filip", 35},
			{"George", 23},
			{"Hanna", 19},
			{"Ivan", 12}
		};
	};*/

	struct Game;
	struct Record;

	void InitLeaderboard(std::map<std::string, int>& list);
	void UpdateScore(std::map<std::string, int>& list, const std::string& name, int score);
	bool VerifNameScore(const std::string& name, int score);
	std::vector<Record> BuildSortedRecords(std::map<std::string, int>& list);
	void DrawLeaderboard(Game& game, sf::RenderWindow& window);
}