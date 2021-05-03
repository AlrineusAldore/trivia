#pragma once

#include <WinSock2.h> //sockets
#include <Windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <bitset>

using std::to_string;
using std::exception;
using std::string;
using std::thread;
using std::vector;
using std::bitset;
using std::endl;
using std::cout;
using std::cin;
using std::map;

#include "json.hpp"
#include "Helper.h" //extra helping funcs 

#define PORT 8820
#define OK_CODE 'E'
#define LOGIN_CODE 420
#define SIGNUP_CODE 69

//magic values
#define MAX_BYTE_NUM 1024
#define BITS_IN_CHAR 8
#define CODE_PART 1
#define LEN_PART 5