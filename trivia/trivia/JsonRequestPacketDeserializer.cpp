#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buffer)
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
SignupRequest JsonRequestPacketDeserializer::deserializeSingupRequest(Buffer buffer)
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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(Buffer buffer)
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

		playersInRoomReq.roomId = stoi(string(j["id"]));
	}

	return playersInRoomReq;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(Buffer buffer)
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

		joinRoomReq.roomId = stoi(string(j["id"]));
	}

	return joinRoomReq;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(Buffer buffer)
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
		createRoomReq.maxUsers = stoi(string(j["maxUsers"]));
		createRoomReq.questionCount = stoi(string(j["questionCount"]));
		createRoomReq.answerTimeout = stoi(string(j["answerTimeout"]));
	}

	return createRoomReq;
}