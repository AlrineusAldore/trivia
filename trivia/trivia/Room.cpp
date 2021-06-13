#include "Room.h"

//Room::Room(RoomData roomData)
//{
//	m_metaData = roomData;
//}

void Room::setRoomData(RoomData roomData)
{
	m_metaData = roomData;
}

RoomData Room::getRoomData()
{
	return m_metaData;
}

//Function adds a user to the room
void Room::addUser(LoggedUser& user)
{
	m_users.push_back(user);
}

//Removes the user from the room
void Room::removeUser(LoggedUser& user)
{
	m_users.erase(remove(m_users.begin(), m_users.end(), user), m_users.end());
}

//Function returns a string vector that contains all the users
vector<string> Room::getAllUsers()
{
	vector<string> users;
	
	for (auto it = m_users.begin(); it != m_users.end(); it++)
	{
		users.push_back(it->getUsername());
	}

	return users;
}