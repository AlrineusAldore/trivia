#pragma once
#include "pch.h"
#include "RequestStructs.h"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<byte> buffer);
	static SignupRequest deserializeSingupRequest(vector<byte> buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(vector<byte> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(vector<byte> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(vector<byte> buffer);


};

