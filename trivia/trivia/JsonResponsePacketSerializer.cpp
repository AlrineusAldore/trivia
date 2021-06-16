#include "JsonResponsePacketSerializer.h"

//Json looks like: { "message": "errMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes)
{
    string jsonStr = "{ \"message\": \"" +errorRes.message+ "\" }";
    return createBuffer(ERROR_CODE, jsonStr);
}

//Json looks like: { "message": "loginMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes)
{
    string jsonStr = "{ \"message\": \"The login was successful!\" }";
    return createBuffer(loginRes.status, jsonStr);
}

//Json looks like: { "message": "signupMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes)
{
    string jsonStr = "{ \"message\": \"You signed up successfuly!\" }";
    return createBuffer(signupRes.status, jsonStr);
}

//String looks like: { "message": "logoutMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutRes)
{
    string jsonStr = "{ \"message\": \"You've logged out successfuly!\" }";
    return createBuffer(logoutRes.status, jsonStr);
}

/* Json looks like:
{
    "rooms":
    [
        {
            "id": int(value),
            "name": "string(value)",
            "maxPlayers": int(value),
            "numOfQuestionsInGame": int(value),
            "timerPerQuestion": int(value),
            "isActive": bool(value),
        },
        {
            "id": int(value),
            "name": "string(value)",
            "maxPlayers": int(value),
            "numOfQuestionsInGame": int(value),
            "timerPerQuestion": int(value),
            "isActive": bool(value),
        },
        //etc
    ]
}
*/
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsRes)
{
    vector<RoomData> rooms = getRoomsRes.rooms; //to shorten lines
    string jsonStr = "{ \"rooms\": [ "; //array of jsons

    //add each json (roomdata) each iteration
    for (int i = 0; i < rooms.size(); i++)
    {
        jsonStr += "{ \"id\": " +rooms[i].id;
        jsonStr += ", \"name\": \"" +rooms[i].name+ "\"";
        jsonStr += ", \"maxPlayers\": " +rooms[i].maxPlayers;
        jsonStr += ", \"numOfQuestionsInGame\": " +rooms[i].numOfQuestionsInGame;
        jsonStr += ", \"timerPerQuestion\": " +rooms[i].timePerQuestion;
        jsonStr += ", \"isActive\": " +rooms[i].isActive;

        if (i == rooms.size() - 1) //if last one close it for good
            jsonStr += " }";
        else
            jsonStr += " }, "; //if in middle then add a comma for another
    }

    jsonStr += " ] }";
    return createBuffer(getRoomsRes.status, jsonStr);
}

/* Json looks like:
{
    "players":
    [
        "string(name)",
        "string(name)",
        //etc
    ]
}
*/
Buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse playersInRoomRes)
{
    vector<string> players = playersInRoomRes.players; //to shorten the lines
    string jsonStr = "{ \"players\": [ ";

    //Get all the inbetween players
    for (int i = 0; i < players.size() - 1; i++)
    {
        jsonStr += "\"" + players[i] + "\", ";
    }

    //Add the last player + ending json
    jsonStr += "\"" + players[players.size()] + "\" ] }";
    
    return createBuffer(GET_PLAYERS_IN_ROOM_CODE, jsonStr);
}

//Json looks like: { "message": "joinRoomMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomRes)
{
    string jsonStr = "{ \"message\": \"You've joined the room!\" }";
    return createBuffer(joinRoomRes.status, jsonStr);
}

//Json looks like: { "message": "createRoomMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomRes)
{
    string jsonStr = "{ \"message\": \"You've created a room successfully!\" }";
    return createBuffer(createRoomRes.status, jsonStr);
}

/* Json looks like:
{
    "topPlayers":
    [
        { "string(firstPlayerName)": float(score) },
        { "string(secondPlayerName)": float(score) },
        //etc (until 5 players)
    ]
}
Note: It's ordered from highest score to lowest
*/
Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse highScoreRes)
{
    string jsonStr = "{ \"topPlayers\": [ ";
    vector<pair<string, float>> stats = highScoreRes.highScores;

    for (int i = 0; i < stats.size(); i++)
    {
        jsonStr += "{ \"" + stats[i].first + "\": " + toStr(stats[i].second);
        if (i < stats.size() - 1) //add comma if not last one
            jsonStr += " }, ";
    }
    jsonStr += " } ] }";

    return createBuffer(highScoreRes.status, jsonStr);
}

/* Json looks like:
{
    "username": "string(value)",
	"gamesPlayed": int(value),
	"totalAnswers": int(value),
	"rightAnswers": int(value),
	"averageAnswerTime": float(value),
	"bestScore": int(value)
}
*/
Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse personalStatsRes)
{
    string jsonStr = "{ ";
    Stats stats = personalStatsRes.stats;
<<<<<<< HEAD
    string avrgAnswerTime = toStr(stats.totalAnswerTime / stats.totalAnswers);
    string gamesPlayed = "" +stats.gamesPlayed, totalAnswers = "" + stats.totalAnswers, rightAnswers = "" + stats.rightAnswers, bestScore = "" + stats.bestScore;
    if (stats.totalAnswers == 0) avrgAnswerTime = "0";
    if (stats.gamesPlayed == 0)
    {
        gamesPlayed = "0";
        totalAnswers = "0";
        rightAnswers = "0";
        bestScore = "0";
    }

=======
    float avrgAnswerTime = 0;
    if (stats.totalAnswers != 0)
        avrgAnswerTime = stats.totalAnswerTime / stats.totalAnswers;
>>>>>>> b8335c145ef5a4ee9781afb0a990bbc307657d95

    jsonStr += "\"username\": \"" + stats.username + "\"";
    jsonStr += ", \"gamesPlayed\": " + gamesPlayed;
    jsonStr += ", \"totalAnswers\": " + totalAnswers;
    jsonStr += ", \"rightAnswers\": " + rightAnswers;
    jsonStr += ", \"averageAnswerTime\": " + avrgAnswerTime;
    jsonStr += ", \"bestScore\": " + bestScore;
    
    jsonStr += " }";

    return createBuffer(personalStatsRes.status, jsonStr);
}

//Json looks like: { "message": "closeRoomMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomRes)
{
    string jsonStr = "{ \"message\": \"The room has been closed\" }";
    return createBuffer(closeRoomRes.status, jsonStr);
    
}

//Json looks like: { "message": "startGameMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameRes)
{
    string jsonStr = "{ \"message\": \"The game has started!\" }";
    return createBuffer(startGameRes.status, jsonStr);
}

/* Json looks like:
{
    "hasGameBegan": bool(value),
    "questionCount": int(value),
    "answerTimeout": int(value),
    "players": [
        "string(username1)",
        "string(username2)",
        //etc
    ]
}
*/
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateRes)
{
    string jsonStr = "{ ";
    vector<string> users = getRoomStateRes.players;

    jsonStr += "\"hasGameBegan\": " + getRoomStateRes.hasGameBegan;
    jsonStr += ", \"questionCount\": " + getRoomStateRes.questionCount;
    jsonStr += ", \"answerTimeout\": " + getRoomStateRes.answerTimeout;
    jsonStr += ", \"players\": [ ";

    for (auto it = users.begin(); it != users.end(); it++)
    {
        jsonStr += "\"" + *it + "\"";

        if (it != users.end()) //if there are more users, add comma
            jsonStr += ", ";
        else                   //if its the last user, close array & json
            jsonStr += " ] }";
    }

    return createBuffer(getRoomStateRes.status, jsonStr);
}

//Json looks like: { "message": "leaveRoomMsg" }
Buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomRes)
{
    string jsonStr = "{ \"message\": \"You have left the room\" }";
    return createBuffer(leaveRoomRes.status, jsonStr);
}



/*
Gets a string and returns it as binary buffer
Input: string str, int code
Output: buffer
*/
Buffer JsonResponsePacketSerializer::createBuffer(int code, string jsonStr)
{
    try
    {
        Buffer buffer;
        buffer.push_back(code);
        auto len = jsonStr.length();

        //push the len to buffer as 4 bytes
        buffer.push_back((len >> 24) & 0xFF);
        buffer.push_back((len >> 16) & 0xFF);
        buffer.push_back((len >> 8) & 0xFF);
        buffer.push_back((len >> 0) & 0xFF);

        for (int i = 0; i < len; i++)
        {
            buffer.push_back(jsonStr[i]);
        }

        return buffer;
    }
    catch (const exception& e)
    {
        cerr << "Error at " << (__FUNCTION__) << ".\tError: " << e.what() << endl;
    }

    return Buffer();
}

string JsonResponsePacketSerializer::toStr(float num)
{
    ostringstream os;
    os << num;
    return os.str();
}