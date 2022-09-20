#pragma once

#include "pch.h"

class SignupException : public exception
{
	virtual const char* what() const throw() {
		return "username is already taken";
	}
};