#pragma once

#include "pch.h"
#include "RequestStructs.h"

class IDatabase
{
public:
	virtual void addNewUser(string username, string password, string email) = 0;

	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username, string password) = 0;
};