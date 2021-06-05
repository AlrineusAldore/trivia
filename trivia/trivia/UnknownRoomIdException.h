#pragma once
#include "pch.h"

class UnknownRoomIdException : public exception
{
	virtual const char* what() const throw() {
		return "Room with given id doesn't exist";
	}
};