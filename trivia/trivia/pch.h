#pragma once

#include <WinSock2.h> //sockets
#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <bitset>
#include <ctime>
#include <map>

#include "json.hpp"

using nlohmann::json;
using std::to_string;
using std::exception;
using std::string;
using std::thread;
using std::vector;
using std::bitset;
using std::endl;
using std::cout;
using std::cerr;
using std::cin;
using std::map;

#define PORT 8820
#define OK_CODE 60
#define LOGIN_CODE 100
#define SIGNUP_CODE 69
#define ERROR_CODE 42

//magic values
#define MAX_BYTE_NUM 1024
#define BITS_IN_CHAR 8
#define CODE_PART 1
#define LEN_PART 5
#define LEN_LEN 4