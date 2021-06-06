#pragma once

#include "pch.h"

class LoggedUser
{
private:
	string m_username;

public:
	LoggedUser(string username) { m_username = username; }

	string getUsername() { return m_username; }

	friend bool operator== (const LoggedUser& user1, const LoggedUser& user2)
	{
		return (user1.m_username == user2.m_username);
	}
	friend bool operator!= (const LoggedUser& user1, const LoggedUser& user2)
	{
		return !operator==(user1, user2);
	}
};