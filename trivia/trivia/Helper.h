#pragma once

#include "pch.h"

class Helper
{
public:
	static void sendData(SOCKET sc, string message);
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	static vector<byte> binStrToBuffer(string binStr);
	static string bufferToBinStr(vector<byte> buffer);
};

