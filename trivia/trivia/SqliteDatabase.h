#pragma once
#include "IDatabase.h"

class SqliteDatabase : public IDatabase
{
private:
	sqlite3* _db;

	void checkResult(int res, string subject);
	Stats* getStatsOfUser(string username);

public:
	SqliteDatabase();
	~SqliteDatabase();

	virtual void addNewUser(string username, string password, string email);

	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);

	virtual list<Question> getQuestions(int numOfQuestions);
	virtual float getPlayerAverageAnswerTime(string username);
	virtual int getNumOfCorrectAnswers(string username);
	virtual int getNumOfTotalAnswers(string username);
	virtual int getNumOfPlayerGames(string username);
};

