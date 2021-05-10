#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
private:
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;

public:
	LoginManager(IDatabase* db);
	~LoginManager() = default;

	void signup(string username, string password, string email);
	void login(string username, string password);
	void logout(string username);
};
