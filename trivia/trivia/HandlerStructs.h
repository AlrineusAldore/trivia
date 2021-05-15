#pragma once
#include "pch.h"

class IRequestHandler; //To make compiler recognize and link it since we can't include it

typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
	vector<byte> buffer;
} RequestInfo;

typedef struct RequestResult
{
	vector<byte> buffer;
	IRequestHandler* newHandler;
} RequestResult;