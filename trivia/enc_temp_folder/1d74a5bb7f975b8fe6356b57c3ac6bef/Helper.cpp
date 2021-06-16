#include "Helper.h"

Buffer Helper::getBufferFromClient(SOCKET sc)
{
	Buffer buffer;

	int code = getMessageTypeCode(sc);
	int len = getLenPartFromSocket(sc, 32);
	string binMsg = getStringPartFromSocket(sc, len * 8);

	//code
	buffer.push_back(code);
	//len
	buffer.push_back((len >> 24) & 0xFF);
	buffer.push_back((len >> 16) & 0xFF);
	buffer.push_back((len >> 8) & 0xFF);
	buffer.push_back(len & 0xFF);
	
	//json msg
	Buffer msgBuf = binStrToBuffer(binMsg);
	buffer.insert(buffer.end(), msgBuf.begin(), msgBuf.end());

	return buffer;
}

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(SOCKET sc)
{
	char* s = getPartFromSocket(sc, 8);
	string msg(s);
	if (msg == "")
		return 0;

	int res = binStrToBuffer(msg)[0];
	delete s;
	return  res;
}

/*
void Helper::send_update_message_to_client(SOCKET sc, const string& file_content, const string& second_username, const string& all_users)
{
	//TRACE("all users: %s\n", all_users.c_str())
	const string code = std::to_string(MT_SERVER_UPDATE);
	const string current_file_size = getPaddedNumber(file_content.size(), 5);
	const string username_size = getPaddedNumber(second_username.size(), 2);
	const string all_users_size = getPaddedNumber(all_users.size(), 5);
	const string res = code + current_file_size + file_content + username_size + second_username + all_users_size + all_users;
	//TRACE("message: %s\n", res.c_str());
	sendData(sc, res);
}*/

// recieve data from socket according byteSize
// returns the data as int
int Helper::getLenPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	Buffer buffer = binStrToBuffer(s);
	int num = int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));
	return num;
}

// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	string res(s);
	return res;
}

// return string after padding zeros if necessary
string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}


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
		string s = " - Error while recieving from socket: ";
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
	Buffer buffer;

	//Get the len part of the buffer
	for (int i = 0; i < binStr.length(); i += 8) //iterate for each byte
	{
		bitset<BITS_IN_CHAR> currByte(binStr.substr(i, BITS_IN_CHAR)); //get each byte
		buffer.push_back(currByte.to_ulong());
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