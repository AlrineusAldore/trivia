#include "Room.h"

//Function adds a user to the room
void Room::addUser(LoggedUser& user)
{
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser& user)
{
	
}

vector<string> getAllUsers();