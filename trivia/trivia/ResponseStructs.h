#pragma once

#include "pch.h"

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
