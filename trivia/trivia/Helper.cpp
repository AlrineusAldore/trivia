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

/*
Function gets a string representing buffer and turns it into buffer
Input: binStr
Output: buffer
*/
vector<byte> Helper::binStrToBuffer(string binStr)
{
	vector<byte> buffer;
	int len = 0;

	bitset<BITS_IN_CHAR> status(binStr);
	buffer.push_back(status.to_ulong());

	//Get the len part of the buffer
	for (int i = CODE_PART; i < LEN_PART; i++) //iterate for each byte
	{
		bitset<BITS_IN_CHAR> lenByte(binStr.substr(i * BITS_IN_CHAR, BITS_IN_CHAR)); //get each byte
		len += lenByte.to_ulong();
		buffer.push_back(lenByte.to_ulong());
	}
	
	//Get each byte in the message
	for (int i = LEN_PART; i < binStr.length() / BITS_IN_CHAR; i++)
	{
		bitset<BITS_IN_CHAR> strByte(binStr.substr(i * BITS_IN_CHAR, BITS_IN_CHAR)); //get each byte
		buffer.push_back(strByte.to_ulong());
	}
	
	return buffer;
}

/*
Function gets buffer and turns it into a binary string, then returns it
Input: buffer
Output: binStr
*/
string Helper::bufferToBinStr(vector<byte> buffer)
{
	string binStr = "";

	//Convert all of buffer's "bytes" to actual binary and put them in a string
	for (int i = 0; i < buffer.size(); i++)
	{
		binStr += bitset<BITS_IN_CHAR>(buffer[i]).to_string();
	}

	return binStr;
}

/*
Function calculates the score of the given stats with a formula
Input: stats
Output: score
*/
float Helper::calculateScore(Stats stats)
{
	float avrgTimePerQuestion = stats.totalAnswers / stats.totalAnswerTime;
	int wrongAnswers = stats.totalAnswers - stats.rightAnswers;
	
	//formula that calculates score
	float score = 10 * ((stats.rightAnswers / avrgTimePerQuestion) * 10 + 20 - wrongAnswers + 20 * stats.rightAnswers);
	
	return score;
}

//Function gets an object and turns it into a string
template <typename T> string Helper::toStr(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}