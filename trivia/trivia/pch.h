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

using nlohmann::json;
using std::to_string;
using std::exception;
using std::string;
using std::thread;
using std::vector;
using std::bitset;
using std::list;
using std::stoi;
using std::stof;
using std::endl;
using std::cout;
using std::cerr;
using std::cin;
using std::map;
using std::advance;

#define PORT 8820
#define OK_CODE 60
#define LOGIN_CODE 100
#define SIGNUP_CODE 69
#define ERROR_CODE 42
#define DB_FILE_NAME "triviaDB.sqlite"
#define USER_NOT_FOUND -1
#define ERROR_EMPTY_FIELD -1

//magic values
#define MAX_BYTE_NUM 1024
#define MAX_QUESTIONS 10
#define BITS_IN_CHAR 8
#define CODE_PART 1
#define LEN_PART 5
#define LEN_LEN 4
#define ENDL '\n'