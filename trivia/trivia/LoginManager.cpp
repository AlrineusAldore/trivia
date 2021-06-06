#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db)
{
	m_database = db;
}

/*
Function signs up a new user if the username isn't taken
Input: username, password, email
Output: throws error
*/
void LoginManager::signup(string username, string password, string email)
{
	if (m_database->doesUserExist(username))
		throw SignupException();
	else
	{
		m_database->addNewUser(username, password, email);
		m_loggedUsers.push_back(LoggedUser(username));
	}
}

/*
Function logs in a person if their username and password match
Input: username, password
Output: throws error
*/
void LoginManager::login(string username, string password)
{
	if (m_database->doesPasswordMatch(username, password))
	{
		m_loggedUsers.push_back(LoggedUser(username));
	}
	else
		throw LoginException();
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