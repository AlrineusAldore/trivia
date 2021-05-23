#pragma once

#include "pch.h"
#include "LoggedUser.h"

typedef struct RoomData RoomData;

class Room
{
private:
	RoomData m_metaData;
	vector<LoggedUser> m_users;

public:
	void addUser(LoggedUser& user);
	void removeUser(LoggedUser& user);
	vector<string> getAllUsers();
};

struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};