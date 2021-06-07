#pragma once

#include "Helper.h"
#include "ResponseStructs.h"

class JsonResponsePacketSerializer
{
private:
	static Buffer createBuffer(int code, string jsonStr);

public:
	static Buffer serializeResponse(ErrorResponse errorRes);
	static Buffer serializeResponse(LoginResponse loginRes);
	static Buffer serializeResponse(SignupResponse signupRes);

	static Buffer serializeResponse(LogoutResponse logoutRes);
	static Buffer serializeResponse(GetRoomsResponse getRoomsRes);
	static Buffer serializeResponse(GetPlayersInRoomResponse playersInRoomRes);
	static Buffer serializeResponse(JoinRoomResponse joinRoomRes);
	static Buffer serializeResponse(CreateRoomResponse createRoomRes);
	static Buffer serializeResponse(GetHighScoreResponse highScoreRes);
	static Buffer serializeResponse(GetPersonalStatsResponse personalStatsRes);
};

