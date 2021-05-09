#pragma once
#include "pch.h"
#include "RequestStructs.h"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializerLoginRequest(vector<byte> buffer);
	static SignupRequest deserializerSingupRequest(vector<byte> buffer);
};

