#pragma once

#include "RequestStructs.h"
#include "TablesStructs.h"

class IDatabase
{
public:
	virtual void addNewUser(string username, string password, string email) = 0;

	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username, string password) = 0;

	virtual list<Question> getQuestions(int numOfQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(string username) = 0;
	virtual int getNumOfCorrectAnswers(string username) = 0;
	virtual int getNumOfTotalAnswers(string username) = 0;
	virtual int getNumOfPlayerGames(string username) = 0;

	virtual Stats getStatsOfUser(string username) = 0;
	virtual vector<string> getAllUsers() = 0;
};

class Temp : IDatabase
{
	virtual void addNewUser(string username, string password, string email);

	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);

	virtual list<Question> getQuestions(int numOfQuestions);
	virtual float getPlayerAverageAnswerTime(string username);
	virtual int getNumOfCorrectAnswers(string username);
	virtual int getNumOfTotalAnswers(string username);
	virtual int getNumOfPlayerGames(string username);

	virtual Stats getStatsOfUser(string username);
	virtual vector<string> getAllUsers();
};