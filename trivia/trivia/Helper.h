#pragma once

#include "pch.h"

class Helper
{
public:
	static void sendData(SOCKET sc, std::string message);
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
};

