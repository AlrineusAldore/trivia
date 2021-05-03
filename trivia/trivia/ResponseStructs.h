#pragma once

#include "pch.h"

struct ErrorResponse
{
	string message;
}; typedef ErrorResponse;

struct LoginResponse
{
	unsigned int status;
}; typedef LoginResponse;

struct SignupResponse
{
	unsigned int status;
}; typedef SignupResponse;
