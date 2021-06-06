#pragma once
#include "pch.h"

class IrrelevantRoomMemberException : public exception
{
	virtual const char* what() const throw() {
		return "Client sent an irrelevant request that is not related to RoomMember";
	}
};