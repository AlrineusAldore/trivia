#pragma once
#include "RoomData.h"
#include "TablesStructs.h"

typedef struct ErrorResponse
{
	string message;
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

//Get structs

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse
{
	unsigned int status;
	vector<pair<string, float>> highScores;
} GetHighScoreResponse;

typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	Stats stats;
} GetPersonalStatsResponse;

//other structs

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

//V3.0.0 structs

typedef struct CloseRoomResponse
{
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegan;
	vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
} LeaveRoomResponse;

//V4 structs

//struct that'll be inside another struct
typedef struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

typedef struct LeaveGameResponse
{
	unsigned int status;
} LeaveGameResponse;

typedef struct GetQuestionResponse
{
	unsigned int status;
	string question;
	map<unsigned int, string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
} SubmitAnswerResponse;

typedef struct GetGameResultsResponse
{
	unsigned int status;
	vector<PlayerResults> results;
} GetGameResultsResponse;