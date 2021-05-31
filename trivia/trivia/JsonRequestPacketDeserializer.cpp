#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<byte> buffer)
{
	LoginRequest lr { "", "" };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == LOGIN_CODE)
	{
		for (int i = 1; i < 5; i++)
		{
			len += buffer[i];
		}

		for (int i = 5; i < buffer.size(); i++)
		{
			str += buffer[i];
		}
		
		j = json::parse(str);

		lr.password = j["password"];
		lr.username = j["username"];
	}

	return lr;
}

/*

*/
SignupRequest JsonRequestPacketDeserializer::deserializeSingupRequest(vector<byte> buffer)
{
	SignupRequest sr { "", "", "" };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == SIGNUP_CODE)
	{
		for (int i = 1; i < 5; i++)
		{
			len += buffer[i];
		}

		for (int i = 5; i < buffer.size(); i++)
		{
			str += buffer[i];
		}

		j = json::parse(str);

		sr.username = j["username"];
		sr.password = j["password"];
		sr.email = j["email"];
	}

	return sr;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(vector<byte> buffer)
{
	GetPlayersInRoomRequest playersInRoomReq { ERROR_INVALID_ROOM_ID };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == GET_PLAYERS_IN_ROOM_CODE)
	{
		for (int i = 1; i < 5; i++)
		{
			len += buffer[i];
		}

		for (int i = 5; i < buffer.size(); i++)
		{
			str += buffer[i];
		}

		j = json::parse(str);

		playersInRoomReq.roomId = j["id"];
	}

	return playersInRoomReq;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(vector<byte> buffer)
{
	JoinRoomRequest joinRoomReq { ERROR_INVALID_ROOM_ID };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == CREATE_JOIN_ROOM_CODE)
	{
		for (int i = 1; i < 5; i++)
		{
			len += buffer[i];
		}

		for (int i = 5; i < buffer.size(); i++)
		{
			str += buffer[i];
		}

		j = json::parse(str);

		joinRoomReq.roomId = j["id"];
	}

	return joinRoomReq;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(vector<byte> buffer)
{
	CreateRoomRequest createRoomReq { "", ERROR, ERROR, ERROR };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == CREATE_JOIN_ROOM_CODE)
	{
		for (int i = 1; i < 5; i++)
		{
			len += buffer[i];
		}

		for (int i = 5; i < buffer.size(); i++)
		{
			str += buffer[i];
		}

		j = json::parse(str);

		createRoomReq.roomName = j["roomName"];
		createRoomReq.maxUsers = j["maxUsers"];
		createRoomReq.questionCount = j["questionCount"];
		createRoomReq.answerTimeout = j["answerTimeout"];
	}

	return createRoomReq;
}