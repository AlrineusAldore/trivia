#pragma once
#include "pch.h"

struct LoginRequest
{
	string username;
	string password;
}typedef LoginRequest;

struct SignupRequest
{
	string username;
	string password;
	string email;
}typedef SignupRequest;

typedef SignupRequest User;