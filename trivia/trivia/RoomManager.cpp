#include "RoomManager.h"

RoomManager::RoomManager()
{
	m_highestId = 0;
}

//Creates a room and adds it to the room list. Returns room's id
unsigned int RoomManager::createRoom(LoggedUser& user, RoomData roomData)
{
	roomData.id = ++m_highestId; //Makes sure each room has its own id

	Room* room = new Room(roomData);
	room->addUser(user);
	m_rooms.insert(make_pair( roomData.id, *room ));

	return roomData.id;
}

//Removes a room from the room list and deletes it
void RoomManager::deleteRoom(unsigned int id)
{
	Room room = getRoom(id);
	m_rooms.erase(id);
	delete &room;
}

//Returns if the room is in a state of waiting for a game to start or mid game
unsigned int RoomManager::getRoomState(unsigned int id)
{
	return getRoom(id).getRoomData().isActive;
}

//Function returns a vector containing the room data of every room
vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> roomDatas;

	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		roomDatas.push_back(it->second.getRoomData());
	}

	return roomDatas;
}

//Get room based on id
Room& RoomManager::getRoom(unsigned int id)
{
	//throw exception if there isn't a room with this id
	if (doesRoomExist(id))
		return m_rooms[id];
	
	throw UnknownRoomIdException();
}

bool RoomManager::doesRoomExist(unsigned int id)
{
	return m_rooms.count(id) > 0;
}