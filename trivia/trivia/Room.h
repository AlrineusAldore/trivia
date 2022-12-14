#pragma once
#include "RoomData.h"
#include "LoggedUser.h"

class Room
{
private:
	RoomData m_metaData;
	vector<LoggedUser> m_users;

public:
	Room(RoomData roomData);
	Room();
	RoomData getRoomData();

	void addUser(LoggedUser& user);
	void removeUser(LoggedUser& user);
	vector<string> getAllUsers();
};
