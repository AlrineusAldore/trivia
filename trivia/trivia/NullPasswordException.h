#pragma once

#include "pch.h"

class NullPasswordException : public exception
{
	virtual const char* what() const throw() {
		return "Error, password is empty";
	}
};