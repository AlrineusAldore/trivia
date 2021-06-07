#pragma once
#include "Room.h"
#include "AllExceptions.h"

class RoomManager
{
private:
	map<unsigned int, Room> m_rooms;
	unsigned int m_highestId;

public:
	RoomManager();

	void createRoom(LoggedUser& user, RoomData roomData);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	vector<RoomData> getRooms();

	Room& getRoom(int id);
};

