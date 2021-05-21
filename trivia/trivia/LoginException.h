#pragma once

#include "pch.h"

class LoginException : public exception
{
	virtual const char* what() const throw() { 
		return "password didn't match to username. couldn't log in"; 
	}
};