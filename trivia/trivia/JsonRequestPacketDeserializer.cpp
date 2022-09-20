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

		lr.username = j.value("username", "");
		lr.password = j.value("password", "");
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
		
		sr.username = j.value("username", "");
		sr.password = j.value("password", "");
		sr.email = j.value("email", "");
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

		playersInRoomReq.roomId = j.value("roomId", 0);
	}

	return playersInRoomReq;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(Buffer buffer)
{
	JoinRoomRequest joinRoomReq { ERROR_INVALID_ROOM_ID };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == JOIN_ROOM_CODE)
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

		joinRoomReq.roomId = j.value("roomId", 0);
	}

	return joinRoomReq;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(Buffer buffer)
{
	CreateRoomRequest createRoomReq { "", ERROR, ERROR, ERROR };
	int len = 0;
	string str = "";
	json j;

	if (buffer[0] == CREATE_ROOM_CODE)
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

		createRoomReq.roomName = j.value("roomName", "");
		createRoomReq.maxUsers = j.value("maxUsers", 0);
		createRoomReq.questionCount = j.value("questionCount", 0);
		createRoomReq.answerTimeout = j.value("answerTimeout", 0);
	}

	return createRoomReq;
}