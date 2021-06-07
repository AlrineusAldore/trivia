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
            "id": int(something),
            "name": "string(something)",
            "maxPlayers": int(something),
            "numOfQuestionsInGame": int(something),
            "timerPerQuestion": int(something),
            "isActive": bool(something),
        },
        {
            "id": int(something),
            "name": "string(something)",
            "maxPlayers": int(something),
            "numOfQuestionsInGame": int(something),
            "timerPerQuestion": int(something),
            "isActive": bool(something),
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
        jsonStr += "{ \"" + stats[i].first + "\": " + Helper::toStr(stats[i].second);
        if (i < stats.size() - 1) //add comma if not last one
            jsonStr += " }, ";
    }
    jsonStr += " } ] }";

    return createBuffer(highScoreRes.status, jsonStr);
}

/* Json looks like:
{
    "username": "string(something)",
	"gamesPlayed": int(something),
	"totalAnswers": int(something),
	"rightAnswers": int(something),
	"averageAnswerTime": float(something),
	"bestScore": int(something)
}
*/
Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse personalStatsRes)
{
    string jsonStr = "{ ";
    Stats stats = personalStatsRes.stats;
    float avrgAnswerTime = stats.totalAnswerTime / stats.totalAnswers;

    jsonStr += "\"username\": \"" + stats.username + "\"";
    jsonStr += ", \"gamesPlayed\": " + stats.gamesPlayed;
    jsonStr += ", \"totalAnswers\": " + stats.totalAnswers;
    jsonStr += ", \"rightAnswers\": " + stats.rightAnswers;
    jsonStr += ", \"averageAnswerTime\": " + Helper::toStr(avrgAnswerTime);
    jsonStr += ", \"bestScore\": " + stats.bestScore;
    
    jsonStr += " }";

    return createBuffer(personalStatsRes.status, jsonStr);
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