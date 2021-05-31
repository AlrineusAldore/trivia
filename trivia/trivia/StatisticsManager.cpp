#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db)
{
	m_database = db;
}

/*
Function returns the top high scores in order
Input: none
Output: highScores
*/
vector<pair<string, float>> StatisticsManager::getHighScore()
{
	vector<pair<string, float>> highScores;
	vector<string> usernames = m_database->getAllUsers();

	//Fill the vector with pairs of scores not in order
	for (int i = 0; i < usernames.size(); i++)
	{
		Stats stats = m_database->getStatsOfUser(usernames[i]);
		highScores.push_back(make_pair(usernames[i], Helper::calculateScore(stats)));
	}

	//Sort it from highest score to lowest
	sort(highScores.begin(), highScores.end(), Helper::sortBySec);

	//Erase all high scores after the maximum number of them
	if (highScores.size() > MAX_HIGHSCORES)
		highScores.erase(highScores.begin() + MAX_HIGHSCORES, highScores.end());

	return highScores;
}

Stats StatisticsManager::getUserStatistics(string username)
{
	return m_database->getStatsOfUser(username);
}

