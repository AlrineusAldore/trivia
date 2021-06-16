#pragma once
#include "pch.h"
#include "ResponseStructs.h"

class Helper
{
public:
	static Buffer getBufferFromClient(SOCKET sc);

	static int getMessageTypeCode(SOCKET sc);
	static int getLenPartFromSocket(SOCKET sc, int bytesNum);
	static string getStringPartFromSocket(SOCKET sc, int bytesNum);
	//static void send_update_message_to_client(SOCKET sc, const string& file_content, const string& second_username, const string& all_users);
	static string getPaddedNumber(int num, int digits);

	static void sendData(SOCKET sc, string message);
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	static vector<byte> binStrToBuffer(string binStr);
	static string bufferToBinStr(vector<byte> buffer);
	static Buffer strToBuffer(string str);
	static string bufferToStr(Buffer buffer);

	static float calculateScore(Stats stats);
	template <typename T> static string toStr(const T& t);
	static bool sortBySec(const pair<string, float>& a, const pair<string, float>& b);

	static GetRoomStateResponse putRoomDataInRoomState(RoomData roomData, vector<string> users);



	static void sus();
};
