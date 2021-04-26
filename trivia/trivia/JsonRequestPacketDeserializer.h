#pragma once
#include "pch.h"
#include "StructsRequest.h"

class JsonRequestPacketDeserializer
{
	static LoginRequest deserializerLoginRequest(vector<byte> buffer);
	static SingupRequest deserializerSingupRequest(vector<byte> buffer);
};

