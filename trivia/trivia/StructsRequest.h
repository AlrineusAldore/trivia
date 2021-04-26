#pragma once
#include "pch.h"

struct LoginRequest
{
	string username;
	string password;
};

struct SingupRequest
{
	string username;
	string password;
	string email;
};