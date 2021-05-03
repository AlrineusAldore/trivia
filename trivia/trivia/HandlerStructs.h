#pragma once

#include "pch.h"
#include "IRequestHandler.h"

struct RequestInfo
{
	//CTime recivalTime;
};
struct RequestResult
{
	vector<byte> response;
	IRequestHandler* newHandler;
} typedef RequestResult;