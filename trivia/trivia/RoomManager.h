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
	void deleteRoom(unsigned int id);
	unsigned int getRoomState(unsigned int id);
	vector<RoomData> getRooms();

	Room& getRoom(unsigned int id);
	bool doesRoomExist(unsigned int id);
};

