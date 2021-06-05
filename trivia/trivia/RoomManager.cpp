#include "RoomManager.h"

RoomManager::RoomManager()
{
	m_highestId = 0;
}

//Creates a room and adds it to the room list
void RoomManager::createRoom(LoggedUser& user, RoomData roomData)
{
	roomData.id = ++m_highestId; //Makes sure each room has its own id

	Room* room = new Room(roomData);
	room->addUser(user);
	m_rooms.insert({ roomData.id, *room });
}

//Removes a room from the room list and deletes it
void RoomManager::deleteRoom(int id)
{
	Room room = m_rooms[id];
	m_rooms.erase(id);
	delete &room;
}

//Returns if the room is in a state of waiting for a game to start or mid game
unsigned int RoomManager::getRoomState(int id)
{
	return m_rooms[id].getRoomData().isActive;
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
Room& RoomManager::getRoom(int id)
{
	//throw exception if there isn't a room with this id
	if (m_rooms.count(id) > 0)
		return m_rooms[id];
	
	throw UnknownRoomIdException();
}