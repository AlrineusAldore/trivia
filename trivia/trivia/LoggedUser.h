#pragma once

#include "pch.h"

class LoggedUser
{
private:
	string m_username;

public:
	LoggedUser(string username) { m_username = username; }

	string getUsername() { return m_username; }
};