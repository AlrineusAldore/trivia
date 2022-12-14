#pragma once
#include "ResponseStructs.h"

class JsonResponsePacketSerializer
{
private:
	static Buffer createBuffer(int code, string jsonStr);
	template <typename T>
	static string toStr(const T& t);

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

	static Buffer serializeResponse(CloseRoomResponse closeRoomRes);
	static Buffer serializeResponse(StartGameResponse startGameRes);
	static Buffer serializeResponse(GetRoomStateResponse getRoomStateRes);
	static Buffer serializeResponse(LeaveRoomResponse leaveRoomRes);
};

