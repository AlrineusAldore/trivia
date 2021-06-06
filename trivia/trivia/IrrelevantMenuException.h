#pragma once
#include "pch.h"

class IrrelevantMenuException : public exception
{
	virtual const char* what() const throw() {
		return "Client sent an irrelevant request that is not from the Menu";
	}
};