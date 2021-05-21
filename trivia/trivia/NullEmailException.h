#pragma once

#include "pch.h"

class NullEmailException : public exception
{
	virtual const char* what() const throw() {
		return "Error, email is empty";
	}
};