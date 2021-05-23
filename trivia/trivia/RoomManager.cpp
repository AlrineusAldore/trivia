#include "RoomManager.h"

//Creates a room and adds it to the room list
void RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
	Room* room = new Room(roomData);
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