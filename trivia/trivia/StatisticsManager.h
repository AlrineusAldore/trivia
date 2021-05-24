#pragma once
#include "pch.h"
#include "IDatabase.h"

class StatisticsManager
{
private:
	IDatabase* m_database;

public:
	StatisticsManager(IDatabase* db);

	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);
};

