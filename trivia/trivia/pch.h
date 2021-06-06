#pragma once

#include <WinSock2.h> //sockets
#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <bitset>
#include <ctime>
#include <list>
#include <io.h>
#include <map>

#include "json.hpp"
#include "sqlite3.h"

using std::ostringstream;
using nlohmann::json;
using std::exception;
using std::make_pair;
using std::to_string;
using std::advance;
using std::string;
using std::thread;
using std::vector;
using std::bitset;
using std::list;
using std::pair;
using std::stoi;
using std::stof;
using std::endl;
using std::cout;
using std::cerr;
using std::cin;
using std::map;

typedef vector<byte> Buffer;

#undef ERROR //un-define it
#define ERROR -1 //redefine it with the new value

#define PORT 8820
#define DB_FILE_NAME "triviaDB.sqlite"
#define USER_NOT_FOUND	ERROR
#define ERROR_EMPTY_FIELD	ERROR
#define ERROR_INVALID_ROOM_ID	ERROR
#define UNINITIALIZED	ERROR

//codes
#define OK_CODE 60
#define LOGIN_CODE 100
#define SIGNUP_CODE 69
#define ERROR_CODE 42
#define GET_PLAYERS_IN_ROOM_CODE 3
#define CREATE_ROOM_CODE 2
#define JOIN_ROOM_CODE 1
#define GET_PERSONAL_STATS_CODE 11
//codes without deserializer
#define GET_HIGH_SCORE_CODE 10
#define LOGOUT_CODE 9
#define GET_ROOMS_CODE 8
#define CLOSE_ROOM_CODE 7
#define START_GAME_CODE 6
#define GET_ROOM_STATE_CODE 5
#define LEAVE_ROOM_CODE 4

//magic values
#define MAX_BYTE_NUM 1024
#define MAX_HIGHSCORES 5
#define MAX_QUESTIONS 10
#define BITS_IN_CHAR 8
#define CODE_PART 1
#define LEN_PART 5
#define LEN_LEN 4
#define ENDL '\n'