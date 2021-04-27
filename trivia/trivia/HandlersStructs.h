#pragma once
#include "pch.h"
#include "IRequestHandler.h"

struct RequestResult
{
	vector<byte> buffer;
	IRequestHandler* newHandler;
}typedef RequestResult;

struct RequestInfo
{
	//Requestid id;
	std::time_t receivalTime;
	vector<byte> buffer;
}typedef RequestInfo;
