#pragma once

#include "pch.h"
#include "ResponseStructs.h"

class JsonResponsePacketSerializer
{
private:
	vector<byte> unpackJsonResponse(string strBin);

public:
	static vector<byte> serializeResponse(ErrorResponse errorRes);
	static vector<byte> serializeResponse(LoginResponse loginRes);
	static vector<byte> serializeResponse(SignupResponse signupRes);
};

