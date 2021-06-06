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

//Gets string representing buffer and turns it into buffer
Buffer Helper::strToBuffer(string str)
{
	Buffer buffer;
	for (int i = 0; i < str.size(); i++)
		buffer.push_back(str[i]);

	return buffer;
}

//Gets a buffer and turns it into a string representing a buffer
string Helper::bufferToStr(Buffer buffer)
{
	string str = "";
	for (const auto it : buffer)
		str += it;

	return str;
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

//Function helps sorting by the second element instead of first
bool Helper::sortBySec(const pair<string, float>& a, const pair<string, float>& b)
{
	return (a.second < b.second);
}

GetRoomStateResponse Helper::putRoomDataInRoomState(RoomData roomData, vector<string> users)
{
	GetRoomStateResponse getRoomStateRes;
	getRoomStateRes.status = GET_ROOM_STATE_CODE;
	getRoomStateRes.answerTimeout = roomData.timePerQuestion;
	getRoomStateRes.hasGameBegan = roomData.isActive;
	getRoomStateRes.questionCount = roomData.numOfQuestionsInGame;
	getRoomStateRes.players = users;

	return getRoomStateRes;
}






void Helper::sus()
{
	cout << endl << R"(MMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNK0xc'......'''...................',:d0NWMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMWNOo:,'................................',:oONMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMNKkl,'....................................',:cxKNWMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMWKx:'.......',............'''''',,,,,,'''''''',;;:ldkKWMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMXx;'....  ...','...''',,;;::ccllloooooollcc:;;,,''''',:oOXMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMWKl'..... ....'',''',;:cclooddxxkkkOOOOOOkxxxxdolc;,''....,l0WMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMW0c'.........'',,,,';clooddxxxkkkOO00000000Okkxxxxdoc:,'....':xNMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMNOc,... ....',,,;;;,,:oddddxxxxkkkOO00000000OOkkxxkkxol:;'.....,dNMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMWKd:,'..  ..',;;;;:::;,coddddxxxxkkkOO000KKKKOOkkkkxxkxxdlc,'.....,kWMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMNo'.... ..',;::::::;;;:odddddxxxxkkkOOOO0KKKK0OOkkkkxxxxddl:,'.....:0WMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMXo'... ..',;:::::;;;;coddddddxxxxkkkOOOO00KK00OOkkkkkkxxddoc;,.....'dNMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMKl'.....',;;:::::;;:coddddxxxxxxkkkkkOOO000K000Okkkkkkxxddol:,.....,kWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMM0:.....',;;;;;;:::clodddddxxdxxxxkkkkkkOO000000OOkkkkxxxxdol:,.....,kWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMO;.....';;;;;;;:lloodddddddddddxxxxxkkkkkOO0KK00Okkkkxxxxddl:,.....'dNMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMWO;. ...,;;;;,;:loooodddddddddddddddxxxxxxxkO00OOkkkkkkxxxxdl:,......oNMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMKc. ...,;;;,,,;:cclloooooooooooddddddddddddxxxxdddddddxxxxddl;'....,OWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMWx'...',;,,''.''',;;:ccclllllloooooooooolllc::;,,,,;;::cooddoc,....;0MMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMKc...','',,,,,''..'',,;;;;:cccloolllcc::;,'.......',,;;;:codl;... .kMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMK:...''',::;''........'',,;;:clooolcc::;,'.....'''...',:cldkx:....'kWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMM0;. .',;;;'...','''''...'',;;ldxkkxlc:;'...'''',;c:'..':ldxkxl...';kWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMKc...;::;,...',,.  .......',:odk00Odc;'..',,'....;lccc::loddxl'.,:lOWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMNd..'::;;,'''',,...........;lodxO0Oko;'..'',,,;:cloooooodxxxxo,.,coOWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMWd'.'::;,,''',,,,'''''....';ldxxk0Okdlc:;;;;::ccclloodoolllool;.':oONMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMXl..';:;;,,'''''''''',,,''';coxkOOkxdoooooollcc::clodxxxxolcol:',cd0NMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMKc..,;;;;;;::c:::::ccc:;,,,;coxkkxxdooddooolllcclloodxxxxxxolc:,;lx0WMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMK:..,;;;::clodddoollcc:;,,,;coxkxxdooooddooolllloooddddxxkkxoccclxkKWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMM0;..',;;:ccloooolcc::;;;,,;:codxxxddoloodolcc::ccloooooooddxdoloxkOKWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMM0c..';;;:cccllcc:;;;,;;;,,;cloodddddooodddollc:;,,,;:ccllllooooxkOOKWMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMWO:',;;;:::::;,,,,,,,;;;;;:clooooddddooooooooolc:;,'',;:cooccoodkO0NMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMWOl;;;;;;,,''''',,,,,,;;;;clodooooolccccloooolcc:;,''.';coc:lx0XNWMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMWKo;,,,,....''',,,,,,,,,,,;cclcc:;;::cllooolcc:;,'.....;lc:o0WMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMKl;,;,','....'',,,,,,'''',;;;;;;:clllllc:;;,'.......';c::dXMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMWk:;;;;;;,'.....',,,,,'''',;;::cccc:::::;;;,...';,'';cc:ckWMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMXo;;:::::;,....,,,;,,,,,,;;::::::ccclddoooc..:cc:;;ccccdXMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMW0c;;:::c:;,'.'loddoooccllcclokkxO0OOKK0Od:,:lll::clccoKWMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMNkc;:::::;,'..;oOOOK0O000kkOKNNXXNNXXKOo;,:loll:clccoKWMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMNOl;;:c::;,,..':dO000KKK00KKXXXXXKOOd:,;:looolllclxXWMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMWKd:;:c::;;,'...,:clxkOkkkOOOkdoolllc;:coddoollo0NMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMNOo;::::;,,'....,;;:;,,;;;:::oxkkdc:codddddxOXWMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMXx::::;;,,''',;cclllcclooddxkxdlccodddddd0WMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMWNKOxxo:,;::;;;;;;;;;:clloooodoolllclloddxdddooxO00XNWMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMWXOxdl:;;,''',,;;;;;::::::::ccccclloooooddddxxxdolllodccdOXNWWMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMWNX0kdl:,',;::;..,,'',;;;;;;::ccccllllllooooddddddxxdoccloodl,;ldkOKKXNWMMMMMMMMMMMMMM
MMMMMMMMMMWXOxol:;,,;;'';;::'.';,''',,;;;;:::cccllllllllooddddddddlc:cloodo;,lxxxkkkOO0KXNWMMMMMMMMM
MMWNXK00Okdc;,,,,,,;;,'';::,.';;,''''',;::::ccclllllllloodddddddoc;,,:clodd:,lkkkkkkkkxxxkO0KNWWMMMM
K0xolc:;;;;;,''',,,;;,'';:;,,;;,''''''',:cccclloooooooodddxxdddoc::::;;:ldd:;okkkkkkkkkkkxxkxkO0XWWM
dlc:;,,,,;;,'''',,,;;,',;;;,',,'',,,,,'',:cclllloooooooodddddol:;::clc;,;colldxxxkxkkkkkkkkkkkkxkO0K
c;,''''',;;,'.',,;;:;,',;;;,.','',,,,,,'',;:clllooooooooooooc:;;:cccool:,,;ldxxxxxkkkkkkkkkkkkkkkkxx
''''''',,;;,''',;;;:;,'',;;,..',,,,,,,,,'''',:ccllllllllcc:;,,;:cccloddolcclddddxxxkkkkkkkkkkkkkkkkk
''''''',,,;;''',;;;:;,'',,,,...',,,,,,,,,,''.'',;;;;::;;;,,,,,;cccloddddoooddddddxxxkkkkkkkkkxxkkOkk)" << endl << endl;
}