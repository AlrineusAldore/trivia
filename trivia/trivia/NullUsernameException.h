#pragma once

#include "pch.h"

class NullUsernameException : public exception
{
	virtual const char* what() const throw() {
		return "Error, username is empty";
	}
};