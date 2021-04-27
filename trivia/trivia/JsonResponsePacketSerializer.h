#pragma once

#include "pch.h"
#include "ResponseStructs.h"

class JsonResponsePacketSerializer
{
private:
	vector<byte> unpackJsonResponse(string strBin);

public:
	vector<byte> serializeResponse(ErrorResponse errorRes);
	vector<byte> serializeResponse(LoginResponse loginRes);
	vector<byte> serializeResponse(SignupResponse signupRes);
};

