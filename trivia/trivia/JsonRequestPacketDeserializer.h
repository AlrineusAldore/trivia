#pragma once
#include "pch.h"
#include "RequestStructs.h"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSingupRequest(Buffer buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(Buffer buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer buffer);


};

