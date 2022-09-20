#pragma once
#include "pch.h"

class IrrelevantLoginException : public exception
{
	virtual const char* what() const throw() {
		return "Client sent an irrelevant request when supposed to login";
	}
};