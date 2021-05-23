#pragma once

#include "Room.h"

class RoomManager
{
private:
	map<unsigned int, Room> m_rooms;

public:
	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	vector<RoomData> getRooms();
};

