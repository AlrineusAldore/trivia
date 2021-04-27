#pragma once
#include "pch.h"

struct LoginRequest
{
	string username;
	string password;
}typedef LoginRequest;

struct SingupRequest
{
	string username;
	string password;
	string email;
}typedef SingupRequest;