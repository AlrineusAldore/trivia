#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes)
{
    string jsonStr = "{ \"message\": \"" +errorRes.message+ "\" }";
    return createBuffer(ERROR_CODE, jsonStr);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes)
{
    string jsonStr = "{ \"message\": \"The login was successful!\" }";
    return createBuffer(loginRes.status, jsonStr);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes)
{
    string jsonStr = "{ \"message\": \"You signed up successfuly!\" }";
    return createBuffer(signupRes.status, jsonStr);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutRes)
{
    string jsonStr = "{ \"message\": \"You've logged out successfuly!\" }";
    return createBuffer(logoutRes.status, jsonStr);
}

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

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomRes)
{
    string jsonStr = "{ \"message\": \"You've joined the room!\" }";
    return createBuffer(joinRoomRes.status, jsonStr);
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomRes)
{
    string jsonStr = "{ \"message\": \"You've created a room successfully!\" }";
    return createBuffer(createRoomRes.status, jsonStr);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse highScoreRes)
{
    string jsonStr = "{ \"topPlayers\": [ ";
    vector<pair<string, float>> stats = highScoreRes.statsList;

    for (int i = 0; i < stats.size(); i++)
    {
        jsonStr += "{ \"" + stats[i].first + "\": " + Helper::toStr(stats[i].second);
        if (i < stats.size() - 1) //add comma if not last one
            jsonStr += " }, ";
    }
    jsonStr += " } ] }";

    return createBuffer(highScoreRes.status, jsonStr);
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