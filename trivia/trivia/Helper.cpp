#include "Helper.h"

void Helper::sendData(SOCKET sc, string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw exception("Error while sending message to client");
	}
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[static_cast<unsigned __int64>(bytesNum) + 1];
	int resSize = recv(sc, data, bytesNum, flags);

	if (resSize == INVALID_SOCKET)
	{
		string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw exception(s.c_str());
	}

	data[resSize] = 0;
	return data;
}