#pragma once
#include "pch.h"

class IRequestHandler; //To make compiler recognize and link it since we can't include it

struct RequestInfo
{
	int id;
	time_t receivalTime;
	vector<byte> buffer;
}typedef RequestInfo;

struct RequestResult
{
	vector<byte> buffer;

	IRequestHandler* newHandler;
}typedef RequestResult;