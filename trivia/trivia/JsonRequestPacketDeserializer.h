#pragma once
#include "pch.h"
#include "RequestStructs.h"

class JsonRequestPacketDeserializer
{
	static LoginRequest deserializerLoginRequest(vector<byte> buffer);
	static SignupRequest deserializerSingupRequest(vector<byte> buffer);
};

