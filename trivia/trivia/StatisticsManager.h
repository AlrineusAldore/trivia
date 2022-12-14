#pragma once
#include "Helper.h"
#include "IDatabase.h"

class StatisticsManager
{
private:
	IDatabase* m_database;

public:
	StatisticsManager(IDatabase* db);

	vector<pair<string, float>> getHighScores();
	Stats getUserStatistics(string username);
};

