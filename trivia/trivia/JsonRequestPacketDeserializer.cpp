#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializerLoginRequest(vector<byte> buffer)
{
	LoginRequest lr;
	lr.password = "";
	lr.username = "";
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
SignupRequest JsonRequestPacketDeserializer::deserializerSingupRequest(vector<byte> buffer)
{
	SignupRequest sr;
	sr.username = "";
	sr.password = "";
	sr.email = "";
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
