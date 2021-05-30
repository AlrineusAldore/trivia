#pragma once
#include "pch.h"
#include "TablesStructs.h"

class Helper
{
public:
	static void sendData(SOCKET sc, string message);
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	static vector<byte> binStrToBuffer(string binStr);
	static string bufferToBinStr(vector<byte> buffer);

	static float calculateScore(Stats stats);
	template <typename T> static string toStr(const T& t);
};

