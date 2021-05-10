#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db)
{
	m_database = db;
}

/*
Function signs up a new user if the username isn't taken
Input: username, password, email
Output: none
*/
void LoginManager::signup(string username, string password, string email)
{
	if (m_database->doesUserExist(username))
		cerr << "username is already taken" << endl;
	else
		m_database->addNewUser(username, password, email);
}

/*
Function logs in a person if their username and password match
Input: username, password
Output: none
*/
void LoginManager::login(string username, string password)
{
	if (m_database->doesPasswordMatch(username, password))
	{
		m_loggedUsers.push_back(LoggedUser(username));
	}
	else
		cerr << "password didn't match to username. coulnd't log in" << endl;
}

/*
Function logs out a person if they are logged in
Input: username
Output: none
*/
void LoginManager::logout(string username)
{
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == username)
		{
			it = m_loggedUsers.erase(it);
			break;
		}
	}
}