#pragma once

#include "pch.h"

class Helper
{
public:
	void sendData(SOCKET sc, std::string message);
	char* getPartFromSocket(SOCKET sc, int bytesNum);
	char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
};

